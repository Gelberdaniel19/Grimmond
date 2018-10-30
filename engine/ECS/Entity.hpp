#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "../geometry/Rectangle.hpp"
#include "../geometry/Vector2D.hpp"

// THIS FILE CONTAINS THE COMPONENT CLASS DEFINITION, THEN THE ENTITY CLASS DEFINITION
class Component;
class Entity;


/**
 * A component gives functionality to an Entity.
 */
class Component
{
protected:
	std::string type;

public:
	// The entity which owns this component
	Entity* entity;

	virtual void Init() {}
	virtual void Update() {}
	virtual void Render() {}

	Component() {}
	virtual ~Component() {}
};


/**
 * An entity is an object that is drawn in the game, such as a player,
 * a powerup, a wall, etc. The entities have a list of components,
 * which give them functionality. Some examples of components are
 * sprites, hitboxes, transform, etc.
 */
class Entity
{
 private:
	bool active = true;
	std::vector<Component*> components;

 public:	
	void Update() { for (Component* c : components) c->Update(); }
	void Render() { for (Component* c : components) c->Render(); }
	bool isActive() { return active; }
	void destroy() { active = false; }

	/**
	 * Adds a component to the entity. If a component of the same
	 * type exists, return false. Otherwise, return true.
	 */
	template <typename T>
	bool addComponent(T* component)
	{
		components.emplace_back(component);
		component->Init();
		return true;
	}

	/**
	 * Gets the first component of the specified type. If the entity does
	 * not have one, returns a nullptr.
	 */
	template <typename T>
	T* getComponent()
	{
		for (Component* c : components) {
			T* t = dynamic_cast<T*>(c);
			if (t)
				return t;
		}
		return nullptr;
	}
};

