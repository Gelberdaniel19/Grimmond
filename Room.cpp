#include "Room.hpp"
#include <random>

Room::Room(int width, int height)
{
	rng.seed(std::random_device()());
	
	// Init map
	for (int i = 0; i < width; i++)
		tiles.push_back(std::vector<int>(height, 0));
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
			tiles[w][h] = 1;
}

void Room::FlagGroundFromTile(std::vector<std::vector<int>>* vec, int x, int y)
{
	if ((*vec)[x][y] != 1)
		return;

	// Mark the tile as flagged and recurse
	(*vec)[x][y] = 5;
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
			if (vec[startX][startY] == 1)
				found = true;

	// Fill the walkable area with flags (tile type = 5)
	FlagGroundFromTile(&vec, startX, startY);

	// All 1's should now be 5's. If not return false
	for (int w = 2; w < vec.size()-2; w++)
		for (int h = 2; h < vec[0].size()-2; h++)
			if (vec[w][h] == 1)
				return false;
	return true;
}

void Room::AddWalls(int x, int y)
{
	// If it's an air tile, make it a wall
	if (tiles[x][y] == 0)
		tiles[x][y] = 2;

	// It must be a ground tile to recurse
	if (tiles[x][y] != 1)
		return;

	tiles[x][y] = 5;
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
			found = true;
	// Then add the walls
	AddWalls(startX, startY);
	// Finally change flagged tiles back to ground tiles
	for (int x = 2; x < tiles.size()-2; x++)
		for (int y = 2; y < tiles[0].size()-2; y++)
			if (tiles[x][y] == 5)
				tiles[x][y] = 1;

	// Get rid of lines of walls extruding into the ground
	bool again;
	do {
		again = false;
		for (int x = 2; x < width-2; x++) {
			for (int y = 2; y < height-2; y++) {
				if (tiles[x][y] == 2) {
					int adjacent = 0;
					if (tiles[x+1][y] == 2) adjacent++;
					if (tiles[x-1][y] == 2) adjacent++;
					if (tiles[x][y+1] == 2) adjacent++;
					if (tiles[x][y-1] == 2) adjacent++;
					if (adjacent == 1) {
						again = true;
						tiles[x][y] = 1;
					}
				}
			}
		}
	} while (again);
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
	} while (tiles[x][y] != 1);

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

void Room::DrawToConsole()
{
	for (int i = 0; i < tiles.size(); i++) {
		for (int j = 0; j < tiles[0].size(); j++) {
			std::cout << tiles[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}
