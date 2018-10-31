#pragma once

#include "Room.hpp"

/**
 * One level consists of a floor containing many maps,
 * each being linked by various portals.
 */
class Level
{
private:
	int level;
	int roomCount;
    Room* rooms[10];

	std::mt19937 rng;

public:
	// Generates random rooms and links them via portal
	Level();
	~Level();

	Room* activeRoom;
};
