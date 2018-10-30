#pragma once

#include <vector>
#include "Entity.hpp"

/**
 * This class holds and operates on every entity in the game.
 */
class EntityManager
{
 private:
	std::vector<Entity*> entities;

 public:
	void Update() { for (Entity* e : entities) e->Update(); }
	void Render() { for (Entity* e : entities) e->Render(); }
	void Refresh()
	{
		for (int i = 0; i < entities.size(); i++) {
			if (!entities[i]->isActive()) {
				entities.erase(entities.begin()+i);
			}
		}
	}

	void addEntity(Entity* e) { entities.emplace_back(e); }
};
