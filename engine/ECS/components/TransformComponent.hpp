#pragma once

#include "../Entity.hpp"

class TransformComponent : public Component
{
public:
	Vector2D position;
	Vector2D velocity;
	Rectangle rectangle;
	float speed = 1;
	
	TransformComponent() {}

	TransformComponent(Rectangle rect)
	{
		rectangle.Equals(rect);
	}
	
	TransformComponent(Vector2D pos)
	{
		position.Equals(pos);
	}

	TransformComponent(Vector2D pos, Vector2D vel, float sp)
	{
		position.Equals(pos);
		velocity.Equals(vel);
		speed = sp;
	}

	TransformComponent(Vector2D pos, Rectangle rect)
	{
		position.Equals(pos);
		rectangle.Equals(rect);
	}

	TransformComponent(Vector2D pos, Vector2D vel, float sp, Rectangle rect)
	{
		position.Equals(pos);
		velocity.Equals(vel);
		speed = sp;
		rectangle.Equals(rect);
	}
};
