#pragma once
#include "Level.hpp"

class World
{
private:
    Level* activeLevel;

public:
    World();
    ~World();
};


World::World()
{
    while (running) {
        // Generate background color
        HSLColor* hsl = GenHSLColor();
        hsl->l += 40;
        HSLColor* hsl2 = new HSLColor(hsl->h, hsl->s, hsl->l-20);
        bgColor = HSLtoRGB(hsl);
        cloudColor = HSLtoRGB(hsl2);
        delete hsl;
        delete hsl2;

        level++;
        activeLevel = new Level(this);
        activeLevel->Start();
    }
}

World::~World()
{
    delete activeLevel;
}
