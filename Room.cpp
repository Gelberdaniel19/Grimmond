#include "Room.hpp"

Room::Room()
{
	tiles(24, std::vector<int>(32, 0));
	GenerateMap(24, 32);
}

void Room::GenerateMap(int width, int height)
{
	
}

/**
 * Inserts a tile on an empty ground tile
 */
void Room::InsertTileOnGround(int type)
{
	int x, y;
	do {
		// Pick random x and y
		x = y = 10;
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
