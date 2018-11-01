#pragma once

#include "../Entity.hpp"

class TransformComponent : public Component
{
public:
	Vector2D position;
	Vector2D velocity;
	Rectangle rectangle;
	float speed = 1;
	
	TransformComponent(Entity* e)
	{
		entity = e;
	}

	TransformComponent(Entity* e, Rectangle rect)
	{
		entity = e;
		rectangle.Equals(rect);
	}
	
	TransformComponent(Entity* e, Vector2D pos)
	{
		entity = e;
		position.Equals(pos);
	}

	TransformComponent(Entity* e, Vector2D pos, Vector2D vel, float sp)
	{
		entity = e;
		position.Equals(pos);
		velocity.Equals(vel);
		speed = sp;
	}

	TransformComponent(Entity* e, Vector2D pos, Rectangle rect)
	{
		entity = e;
		position.Equals(pos);
		rectangle.Equals(rect);
	}

	TransformComponent(Entity* e, Vector2D pos, Vector2D vel, float sp, Rectangle rect)
	{
		entity = e;
		position.Equals(pos);
		velocity.Equals(vel);
		speed = sp;
		rectangle.Equals(rect);
	}

	void Update()
	{
		position.Add(velocity);
	}
};
