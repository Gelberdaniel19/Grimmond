#pragma once

#include "Entity.hpp"
#include "Components.hpp"

class Collision
{
public:
	static bool AABB(Entity* e1, Entity* e2)
	{
		// Return false if no hitbox component, get the hitboxes
		HitboxComponent* h1;
		HitboxComponent* h2;
		if ((h1 = e1->GetComponent<HitboxComponent>()) == nullptr)
			return false;
		if ((h2 = e2->GetComponent<HitboxComponent>()) == nullptr)
			return false;
		Rectangle r1 = h1->hitbox;
		Rectangle r2 = h2->hitbox;

		return AABB(r1, r2);
	}

	static bool AABB(Rectangle r1, Rectangle r2)
	{
		return ((r1.x < r2.x + r2.w) &&
                (r1.x + r1.w > r2.x) &&
                (r1.y < r2.y + r2.h) &&
                (r1.y + r1.h > r2.y));
	}
};
