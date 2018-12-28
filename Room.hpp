#pragma once

#include "globals.hpp"
#include "Systems.hpp"
#include "Level.hpp"
#include <vector>
#include <random>
#include <iostream>

// TILE VALUES DEFINED BELOW
#define AIR 0
#define GROUND 1
#define WALL 2
#define PLAYER 3
#define STAIR 4
#define FLAG 5
// portals:  100-199
// powerups: 200-299
// enemies:  300-399

// TILE COLORS
#define C_GROUND 0, 255, 0
#define C_WALL 30, 30, 30
#define C_PLAYER 247, 147, 26
#define C_PORTAL 191, 0, 255

class Level;

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
	std::mt19937 rng;
	bool portalHit = false;

	void CarveSquare();
	void AddWalls(int x, int y);
	void FlagGroundFromTile(std::vector<std::vector<int>>* vec, int x, int y);
	bool AllAccessible(std::vector<std::vector<int>> vec);

public:
	Level* parent;
	Room(Level* parent, int width, int height);

	void InsertTileOnGround(int type);

	bool IsGroundType(int x, int y);
	bool HasPortal();
	bool HasTile(int type);

	void GenerateMap(int width, int height);
	void DrawToConsole();

	std::vector<std::vector<int>> GetTiles();

	void Play();
};
