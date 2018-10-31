#include "Components.hpp"
#include "Entity.hpp"
#include "Scene.hpp"

#include <iostream>
#include <string>
using namespace std;

int main()
{
	// Create manager and player
	Scene manager;
	Entity player;
	Entity wall;
	manager.AddEntity(&player);
	manager.AddEntity(&wall);

	// Transform testing
    HitboxComponent hc1(10, 10, 10, 10);
	HitboxComponent hc2(19.999, 19.999, 1, 1);
	player.AddComponent<HitboxComponent>(&hc1);
	wall.AddComponent<HitboxComponent>(&hc2);

	manager.Update();
	
	return 0;
}
