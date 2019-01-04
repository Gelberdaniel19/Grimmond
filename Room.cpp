#include "Room.hpp"
#include <random>

void Room::Play()
{
	portalHit = false;

	// Add all the entities
	AutoManager manager(new EntityManager);
	manager->AddSystem<ControlSystem>();
	manager->AddSystem<AISystem>();
	manager->AddSystem<PhysicsSystem>();
	manager->AddSystem<PortalSystem>();
	manager->AddSystem<StairSystem>();
	manager->AddSystem<CloudSystem>();
	manager->AddSystem<CameraSystem>();
	manager->AddSystem<RenderSystem>();

	// Make player (position found later)
	auto& player = manager->AddEntity();
	player.name = "player";
	player.AddComponent<RenderComponent>(2, C_PLAYER);
	player.AddComponent<PhysicsComponent>();
	player.AddComponent<ControlComponent>(500);

	// Makes entities from the generated tilemap
	for (int row = 0; row < tiles.size(); row++) {
		for (int col = 0; col < tiles[0].size(); col++) {
			auto& tile = manager->AddEntity();
			tile.AddComponent<TransformComponent>(row*100, col*100, 100, 100);

			if (tiles[row][col] == GROUND) {
				tile.AddComponent<RenderComponent>(1, C_GROUND);
			} else if (tiles[row][col] == WALL) {
				tile.AddComponent<RenderComponent>(1, C_WALL);
				tile.AddComponent<PhysicsComponent>(false);
			} else if (tiles[row][col] == PLAYER) {
				tile.AddComponent<RenderComponent>(1, C_GROUND);
				player.name = "player";
				player.AddComponent<TransformComponent>(row*100+10, col*100+10, 80, 80);
			} else if (tiles[row][col] == STAIR) {
				tile.AddComponent<RenderComponent>(3, C_STAIR_IN);
				auto& decor = manager->AddEntity();
				decor.AddComponent<TransformComponent>(row*100-20, col*100-20, 140, 140);
				decor.AddComponent<RenderComponent>(2, C_STAIR_OUT);
				decor.AddComponent<StairComponent>(this, &player, &portalHit);
			} else if (tiles[row][col] == ENEMY) {
				tile.AddComponent<RenderComponent>(1, C_GROUND);
				auto& enemy = manager->AddEntity();
				enemy.name = "enemy";
				enemy.AddComponent<TransformComponent>(row*100+25, col*100+25, 50, 50);
				enemy.AddComponent<RenderComponent>(2, 255, 0, 0);
				enemy.AddComponent<AIComponent>(&player, 100);
				enemy.AddComponent<PhysicsComponent>();
			} else if (tiles[row][col] >= 100 && tiles[row][col] < 200) {
				tile.name = "portal";
				std::vector<RGBColor*> pair = parent->colorPairs[tiles[row][col]-100];
				tile.AddComponent<RenderComponent>(3, pair[0]->r, pair[0]->g, pair[0]->b);
				auto& decor = manager->AddEntity();
				decor.AddComponent<TransformComponent>(row*100+20, col*100+20, 60, 60);
				decor.AddComponent<RenderComponent>(3, pair[1]->r, pair[1]->g, pair[1]->b);
				decor.AddComponent<PortalComponent>(
					parent->GetDestRoom(this, tiles[row][col]),
					this,
					&player,
				 	&portalHit);
			} else {
				tile.Destroy();
			}
		}
	}

	// Makes clouds
	std::mt19937 rng;
    rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> distSize(200, 500);
	std::uniform_int_distribution<std::mt19937::result_type> distX(0, 100*MAP_WIDTH+400);
	std::uniform_int_distribution<std::mt19937::result_type> distY(0, 100*MAP_HEIGHT+400);
	std::uniform_int_distribution<std::mt19937::result_type> distVel(0, 100);
	for (int i = 0; i < 20; i++) {
		auto& cloud = manager->AddEntity();
		cloud.name = "cloud";
		cloud.AddComponent<RenderComponent>(0, cloudColor->r, cloudColor->g, cloudColor->b);
		cloud.AddComponent<TransformComponent>((int)distX(rng)-200, (int)distY(rng)-200, distSize(rng), distSize(rng));
		cloud.AddComponent<CloudComponent>((int)distVel(rng)-50, (int)distVel(rng)-50);
	}

	// Preperation view - the level is shown but not started
	SDL_RenderClear(renderer);
	manager->Update(0);
	RenderHUD();
	SDL_RenderPresent(renderer);

	unsigned int timediff = 10;
	while (running && !portalHit) {
		unsigned int starttime = SDL_GetTicks();
		if (timediff < 10)
			SDL_Delay(10-timediff);
		SDL_RenderClear(renderer);

		HandleInput();
		manager->Update((float)timediff/1000);
		RenderHUD();
		SDL_RenderPresent(renderer);

		timediff = SDL_GetTicks() - starttime;
	}
	manager->Purge();
}

Room::Room(Level* p, int width, int height)
{
	parent = p;
	rng.seed(std::random_device()());

	// Init map
	for (int i = 0; i < width; i++)
		tiles.push_back(std::vector<int>(height, AIR));
	GenerateMap(width, height);
}

void Room::CarveSquare()
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> distRoomX(2, tiles.size()-3);
	std::uniform_int_distribution<std::mt19937::result_type> distRoomY(2, tiles[0].size()-3);

	// Make a box
	int x1, x2, y1, y2;
	do {
		x1 = distRoomX(rng);
		x2 = distRoomY(rng);
	} while (abs(x1-x2) <= 2);
	do {
		y1 = distRoomY(rng);
		y2 = distRoomY(rng);
	} while (abs(y1-y2) <= 2);

	// Carve the box
	for (int w = std::min(x1, x2); w < std::max(x1, x2); w++)
		for (int h = std::min(y1, y2); h < std::max(y1, y2); h++)
			tiles[w][h] = GROUND;
}

void Room::FlagGroundFromTile(std::vector<std::vector<int>>* vec, int x, int y)
{
	if ((*vec)[x][y] != GROUND)
		return;

	// Mark the tile as flagged and recurse
	(*vec)[x][y] = FLAG;
	FlagGroundFromTile(vec, x+1, y);
	FlagGroundFromTile(vec, x-1, y);
	FlagGroundFromTile(vec, x, y+1);
	FlagGroundFromTile(vec, x, y-1);
}

bool Room::AllAccessible(std::vector<std::vector<int>> vec)
{
	// Find a ground tile to start on
	int startX, startY;
	bool found = false;
	for (startX = 2; startX < vec.size()-2 && !found; startX++)
		for (startY = 2; startY < vec[0].size()-2 && !found; startY++)
			if (vec[startX][startY] == GROUND)
				found = true;

	// Fill the walkable area with flags (tile type = 5)
	FlagGroundFromTile(&vec, startX, startY);

	// All 1's should now be 5's. If not return false
	for (int w = 2; w < vec.size()-2; w++)
		for (int h = 2; h < vec[0].size()-2; h++)
			if (vec[w][h] == GROUND)
				return false;
	return true;
}

void Room::AddWalls(int x, int y)
{
	// If it's an air tile, make it a wall
	if (tiles[x][y] == AIR)
		tiles[x][y] = WALL;

	// It must be a ground tile to recurse
	if (tiles[x][y] != GROUND)
		return;

	tiles[x][y] = FLAG;
	AddWalls(x, y+1);
	AddWalls(x, y-1);
	AddWalls(x+1, y);
	AddWalls(x+1, y+1);
	AddWalls(x+1, y-1);
	AddWalls(x-1, y);
	AddWalls(x-1, y+1);
	AddWalls(x-1, y-1);
}

void Room::GenerateMap(int width, int height)
{
	// Generate two random points. If their x and y difference is more than 2,
	// make them into a square of ground. Repeat the process between 3 and 7 times.
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> distSquares(4, 8);
	std::uniform_int_distribution<std::mt19937::result_type> distEnemies(4, 10);
	std::uniform_int_distribution<std::mt19937::result_type> distRoomX(2, width-3);
	std::uniform_int_distribution<std::mt19937::result_type> distRoomY(2, height-3);

	// Carve squares of ground
	int squares = distSquares(rng);
	for (int i = 0; i < squares; i++) CarveSquare();

	// Carve more squares until they're all connected
	while (!AllAccessible(tiles))
		CarveSquare();

	// Add walls and change flagged tiles back to ground tiles
	// First, find a tile to start on
	int startX, startY;
	bool found = false;
	for (startX = 2; startX < tiles.size()-2 && !found; startX++)
		for (startY = 2; startY < tiles[0].size()-2 && !found; startY++)
			if (tiles[startX][startY] == GROUND)
				found = true;
	// Then add the walls
	AddWalls(startX, startY);
	// Finally change flagged tiles back to ground tiles
	for (int x = 2; x < tiles.size()-2; x++)
		for (int y = 2; y < tiles[0].size()-2; y++)
			if (tiles[x][y] == FLAG)
				tiles[x][y] = GROUND;

	// Get rid of lines of walls extruding into the ground
	bool again;
	do {
		again = false;
		for (int x = 2; x < width-2; x++) {
			for (int y = 2; y < height-2; y++) {
				if (tiles[x][y] == WALL) {
					int adjacent = 0;
					if (tiles[x+1][y] == WALL) adjacent++;
					if (tiles[x-1][y] == WALL) adjacent++;
					if (tiles[x][y+1] == WALL) adjacent++;
					if (tiles[x][y-1] == WALL) adjacent++;
					if (adjacent == 1) {
						again = true;
						tiles[x][y] = GROUND;
					}
				}
			}
		}
	} while (again);

	// Add enemies
	int enemies = distEnemies(rng);
	for (int i = 0; i < enemies; i++)
		InsertTileOnGround(ENEMY);
}

/**
 * Inserts a tile on an empty ground tile
 */
void Room::InsertTileOnGround(int type)
{
	std::uniform_int_distribution<std::mt19937::result_type> randX(0, tiles.size()-1);
	std::uniform_int_distribution<std::mt19937::result_type> randY(0, tiles[0].size()-1);

	int x, y;
	do {
		x = randX(rng);
		y = randY(rng);
	} while (tiles[x][y] != GROUND);

	tiles[x][y] = type;
}

bool Room::IsGroundType(int x, int y)
{
	return tiles[x][y] != AIR and tiles[x][y] != WALL;
}

bool Room::HasPortal()
{
	for (int i = 0; i < tiles.size(); i++)
		for (int j = 0; j < tiles[0].size(); j++)
			if (tiles[i][j] >= 100 and tiles[i][j] < 200)
				return true;
	return false;
}

bool Room::HasTile(int tile)
{
	for (int i = 0; i < tiles.size(); i++)
		for (int j = 0; j < tiles[0].size(); j++)
			if (tiles[i][j] == tile)
				return true;
	return false;
}

void Room::DrawToConsole()
{
	for (int i = 0; i < tiles.size(); i++) {
		for (int j = 0; j < tiles[0].size(); j++) {
			std::cout << tiles[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

std::vector<std::vector<int>> Room::GetTiles()
{
	return tiles;
}
