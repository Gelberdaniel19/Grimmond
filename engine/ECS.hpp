#pragma once

#include <vector>
#include <array>
#include <bitset>
#include <memory>

#define MAX_COMPONENTS 8


inline std::size_t getComponentTypeID()
{
	static std::size_t lastID = 0;
	return lastID++;
}

template <typename T> std::size_t getComponentTypeID() noexcept
{
	static std::size_t typeID = getComponentTypeID();
	return typeID;
}


class Entity;


/**
 * A component is a block of data given to an entity.
 */
class Component // COMPONENT
{
public:
	Entity* entity;
};


/**
 * An entity is a container of components. No logic.
 */
class Entity // ENTITY
{
private:
	bool active = true;
	std::vector<Component*> components;
public:
	std::string name = "none";
	std::array<std::unique_ptr<Component>, MAX_COMPONENTS> componentArray;
	std::bitset<MAX_COMPONENTS> componentBitset;

	bool IsActive() { return active; }
	bool Destroy() { active = false; }

	template <typename T> bool HasComponent();
	template <typename T, typename ...TArgs> T& AddComponent(TArgs&& ...mArgs);
	template <typename T> T* GetComponent();
};


/**
 * A system is a container of logic. It contains no data and only
 * modifies relevant components.
 */
class System // SYSTEM
{
public:
	std::bitset<MAX_COMPONENTS> componentMask;

	System() {}
	~System() {}

	virtual void Update(double deltatime, std::vector<Entity*>) {}
	template <typename ...T> void AddComponents();
};
using AutoSystem = std::unique_ptr<System>;


/**
 * The EntityManager holds systems and entites, and is responsible
 * for passing to the systems only the entities that each one cares about.
 */
class EntityManager // MANAGER
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::vector<std::unique_ptr<System>> systems;
public:
	void Update(double timedelta);
	void Refresh();
	void Purge();

	Entity& AddEntity();
	template <typename T, typename ...TArgs> T& AddSystem(TArgs&& ...mArgs);
};
using AutoManager = std::unique_ptr<EntityManager>;


template <typename ...T>
void System::AddComponents()
{
	[](...){ }((componentMask[getComponentTypeID<T>()] = 1)...);
}

/**
 * Checks if an entity has a component.
 */
template <typename T>
bool Entity::HasComponent()
{
	return componentBitset[getComponentTypeID<T>()];
}
