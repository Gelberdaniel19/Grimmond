#pragma once
#include "Room.hpp"

class World;

/**
 * One level consists of a floor containing many maps,
 * each being linked by various portals.
 */
class Level
{
private:
	World* world;
	int level;
	int roomCount;
	Room* activeRoom;
	std::vector<Room*> rooms;
	std::mt19937 rng;

public:
	// Generates random rooms and links them via portal
	Level(World* world);
	~Level();

	Room* GetDestRoom(Room* src, int portalnum);
};
