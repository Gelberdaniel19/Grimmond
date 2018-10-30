#pragma once

#include "Entity.hpp"
#include <string>

class Entity;

class Component
{
 protected:
	std::string type;
   
 public:
	// The entity which owns this component
	Entity* entity;

	std::string getType() { return type; }
	
	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}

	Component() {}
	~Component() {}
};
