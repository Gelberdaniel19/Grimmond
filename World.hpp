#pragma once
#include "Level.hpp"

class World
{
private:
    int level = 1;
    Level* activeLevel;

public:
    World();
    ~World();
};


World::World()
{
    activeLevel = new Level(this);
}

World::~World()
{
    delete activeLevel;
}
