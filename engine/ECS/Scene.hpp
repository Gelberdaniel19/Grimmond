#pragma once

#include <vector>
#include <iostream>
#include "Entity.hpp"
#include "Collision.hpp"

/**
 * This class holds and operates on every entity in the game.
 */
class Scene
{
 private:
	std::vector<Entity*> entities;

 public:
	void Update()
	{
		for (Entity* e : entities) e->Update();
		for (Entity* e1 : entities) {
			if (e1->GetComponent<HitboxComponent>() == nullptr)
				continue;
			for (Entity* e2 : entities) {
				if (e2->GetComponent<HitboxComponent>() == nullptr)
					continue;
				if (e1 != e2 && Collision::AABB(e1, e2)) {
					//std::cout << e1->name << " hit " << e2->name << std::endl;
					e1->GetComponent<HitboxComponent>()->ProcessCollision(e2);
				}
			}
		}
	}
	
	void Render() { for (Entity* e : entities) e->Render(); }

	void Refresh()
	{
		for (int i = 0; i < entities.size(); i++) {
			if (!entities[i]->isActive()) {
				entities.erase(entities.begin()+i);
			}
		}
	}

	void AddEntity(Entity* e) { entities.emplace_back(e); }
};
