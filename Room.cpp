#include "Room.hpp"

Room::Room(int width, int height)
{
	rng.seed(std::random_device()());
	
	// Init map
	for (int i = 0; i < width; i++)
		tiles.push_back(std::vector<int>(height, 1));
	GenerateMap(width, height);
}

void Room::GenerateMap(int width, int height)
{
	
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
