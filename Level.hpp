#pragma once
#include "Room.hpp"
#include <random>

class World;
class Room;

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
	bool complete = false;

	// Generates random rooms and links them via portal
	Level(World* world);
	~Level();

	void Start();
	Room* GetDestRoom(Room* src, int portalnum);
};
