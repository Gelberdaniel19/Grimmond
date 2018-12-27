#include "ECS.hpp"

/**
 * Add a component to the entity by type.
 */
template <typename T, typename ...TArgs>
T& Entity::AddComponent(TArgs&& ...mArgs)
{
	T* c(new T(std::forward<TArgs>(mArgs)...));
	c->entity = this;
	components.emplace_back(c);

	std::unique_ptr<Component> uPtr{c};

	componentArray[getComponentTypeID<T>()] = std::move(uPtr);
	componentBitset[getComponentTypeID<T>()] = true;
	return *c;
}

/**
 * Get a component from the entity by type.
 */
template <typename T>
T* Entity::GetComponent()
{
	return static_cast<T*>(componentArray[getComponentTypeID<T>()].get());
}



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
 * Add a system to the manager.
 */
template <typename T, typename ...TArgs>
T& EntityManager::AddSystem(TArgs&& ...mArgs)
{
	T* s(new T(std::forward<TArgs>(mArgs)...));
	std::unique_ptr<System> uPtr{s};
	systems.emplace_back(std::move(uPtr));
	return *s;
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
