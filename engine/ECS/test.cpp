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
	player.name = "player";
	Entity wall;
	wall.name = "wall";
	manager.AddEntity(&player);
	manager.AddEntity(&wall);
	
	TransformComponent playerT(&player);
	playerT.position.Set(45, 42);
	playerT.rectangle.SetSize(10, 10);
	playerT.velocity.Set(1, 1);
	player.AddComponent<TransformComponent>(&playerT);
	TransformComponent wallT(&wall);
	wallT.position.Set(50, 50);
	wallT.rectangle.SetSize(10, 10);
	wall.AddComponent<TransformComponent>(&wallT);

	
	// Hitbox testing
    HitboxComponent hc1(&player);
	HitboxComponent hc2(&wall);
	player.AddComponent<HitboxComponent>(&hc1);
	wall.AddComponent<HitboxComponent>(&hc2);

	cout << "wall at: " << wall.GetComponent<TransformComponent>()->position.x << ","
		 << wall.GetComponent<TransformComponent>()->position.y << endl;	
	cout << "player pos: " << player.GetComponent<TransformComponent>()->position.x << ","
		 << player.GetComponent<TransformComponent>()->position.y << endl;
	cout << "player vel: " << player.GetComponent<TransformComponent>()->velocity.x << ","
		 << player.GetComponent<TransformComponent>()->velocity.y << "\n" << endl;
	
	for (int i = 0; i < 20; i++) {
		manager.Update();
		cout << "player pos: " << player.GetComponent<TransformComponent>()->position.x << ","
			 << player.GetComponent<TransformComponent>()->position.y << endl;
	}
	
	return 0;
}
