#pragma once

#include <vector>
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
	void Update() {
		for (Entity* e : entities) e->Update();
		for (Entity* e1 : entities)
			for (Entity* e2 : entities)
				if (e1 != e2 && Collision::AABB(e1, e2))
					std::cout << "collision" << std::endl;
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
