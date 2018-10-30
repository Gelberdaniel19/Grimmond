#include "Components.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"

#include <iostream>
#include <string>
using namespace std;

int main()
{
	TransformComponent tc;
	tc.position.set(5, 10);

	EntityManager manager;
	Entity player;
	manager.addEntity(&player);
	
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
	
	return 0;
}
