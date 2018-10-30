#pragma once

#include <vector>

/**
 * A room is a part of the level. Rooms are linked together by portals.
 * A portal is given by a tile numbered 100-199, where linked rooms
 * will share one tile of a unique number 100-199. 200 represents the
 * stairs, bringing the player to the next level. 201 represents the
 * player's spawn. The stairs spawn in one room, and the player spawns
 * in one room, at random. 
 */
class Room
{
private:
	std::vector<std::vector<int>> tiles;

public:
	Map();
	~Map();

	void GenerateMap(int width, int height);
};
