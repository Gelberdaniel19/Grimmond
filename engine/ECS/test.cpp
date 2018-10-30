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
	manager.addEntity(&player);

	// Transform testing
	TransformComponent tc;
	tc.position.set(5, 10);
	player.addComponent(&tc);	
	cout << typeid(tc).name() << endl;
	TransformComponent* lmao = player.getComponent<TransformComponent>();
	if (lmao == nullptr) {
		cout << "couldn't find the component" << endl;
		return -1;
	}
	player.getComponent<TransformComponent>()->velocity.set(2,5);
	cout << lmao->position.x() << "," << lmao->position.y() << endl;
	cout << lmao->velocity.x() << "," << lmao->velocity.y() << endl;

	// Hitbox testing
	HitboxComponent hc(10, 20, 5, 5);
	player.addComponent(&hc);
	cout << typeid(hc).name() << endl;
	HitboxComponent* lmao2 = player.getComponent<HitboxComponent>();
	if (lmao == nullptr) {
		cout << "couldn't find the component" << endl;
		return -1;
	}
	player.getComponent<HitboxComponent>()->hitbox.x(4);
	cout << "hitbox: " << lmao2->hitbox.x() << "," << lmao2->hitbox.y() << " "
		 << lmao2->hitbox.w() << "," << lmao2->hitbox.h() << endl;

	// Removing inactive testing
	player.destroy();
	manager.Refresh();
	//cout << lmao2->hitbox.x() << endl;
	
	return 0;
}
