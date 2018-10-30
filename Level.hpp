#pragma once

#include "Map.hpp"

/**
 * One level consists of a floor containing many maps,
 * each being linked by various portals.
 */
class Level
{
public:
	Level();
	~Level();

	Map* activeMap;

private:
	int level;
	int mapCount;
	Map* maps[10];
};
