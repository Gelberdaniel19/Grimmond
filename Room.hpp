#pragma once

#include <vector>

// TILE VALUES DEFINED BELOW
#define AIR 0
#define GROUND 1
#define WALL 2
#define PLAYER 3
#define STAIR 4
// portals:  100-199
// powerups: 200-299
// enemies:  300-399


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
	Room();
	~Room();

	void InsertTileOnGround(int type);
	
	bool IsGroundType(int x, int y);
	bool HasPortal();

	void GenerateMap(int width, int height);
};