#pragma once

#include "../Entity.hpp"

class HitboxComponent : public Component
{
public:
	Rectangle hitbox;

	HitboxComponent() {}
	
	HitboxComponent(Rectangle rect)
	{
		hitbox.Equals(rect);
	}

	HitboxComponent(float x, float y, float w, float h)
	{
		hitbox = Rectangle(x, y, w, h);
	}
};
