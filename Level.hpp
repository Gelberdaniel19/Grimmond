#pragma once
#include "Room.hpp"
#include "colors.hpp"
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
	std::vector<Room*> rooms;
	std::mt19937 rng;

public:
	Room* activeRoom;
	std::vector<std::vector<RGBColor*>> colorPairs;
	bool complete = false;

	// Generates random rooms and links them via portal
	Level(World* world);
	~Level();

	void Start();
	Room* GetDestRoom(Room* src, int portalnum);
};
