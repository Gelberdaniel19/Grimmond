#include "ECS.hpp"


/**
 * For each system, send the timedelta and the appropriate list of entities
 * to be updated. The entities are selected by checking the bitset to make
 * sure that the entity has every component from the mask in the system.
 */
void EntityManager::Update(double timedelta)
{
	for (auto& s : systems) {
		std::vector<Entity*> filtered;
		for (auto& e : entities)
			if ((s->componentMask & e->componentBitset) == s->componentMask)
				filtered.emplace_back(e.get());
		s->Update(timedelta, filtered);
	}

	Refresh();
}

/**
 * Destroy inactive entities.
 */
void EntityManager::Refresh()
{
	for (int i = 0; i < entities.size(); i++)
		if (!entities[i]->IsActive())
			entities.erase(entities.begin() + i);
}

/**
 * Add an entity to the manager.
 */
Entity& EntityManager::AddEntity()
{
	Entity* e = new Entity();
	std::unique_ptr<Entity> uPtr{e};
	entities.emplace_back(std::move(uPtr));
	return *e;
}

void EntityManager::Purge()
{
	for (int i = 0; i < entities.size(); i++)
		entities[i]->Destroy();
	entities.clear();
	this->Update(0);
}
