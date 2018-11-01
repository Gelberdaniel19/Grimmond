#pragma once

#include "../Entity.hpp"
#include "../Components.hpp"
#include <iostream>
#include <string>
#include <cmath>

/**
 * This is a hitbox component, which is a rectangle at a position. The position
 * is offset from the player's TransformComponent position by the amount Vector2D offset.
 */
class HitboxComponent : public Component
{
public:
	Vector2D offset;
	Rectangle hitbox;

	HitboxComponent(Entity* e)
	{
		entity = e;
		hitbox.w = entity->GetComponent<TransformComponent>()->rectangle.w;
        hitbox.h = entity->GetComponent<TransformComponent>()->rectangle.h;
		hitbox.x = entity->GetComponent<TransformComponent>()->position.x + offset.x;
        hitbox.y = entity->GetComponent<TransformComponent>()->position.y + offset.y;
	}
	
	HitboxComponent(Entity* e, float w, float h)
	{
		entity = e;
		hitbox.w = w;
		hitbox.h = h;
		hitbox.x = entity->GetComponent<TransformComponent>()->position.x + offset.x;
		hitbox.y = entity->GetComponent<TransformComponent>()->position.y + offset.y;
	}

	HitboxComponent(Entity* e, float offX, float offY, float w, float h)
	{
		entity = e;
		offset.x = offX;
		offset.y = offY;
		hitbox.w = w;
		hitbox.x = entity->GetComponent<TransformComponent>()->position.x + offset.x;	
        hitbox.y = entity->GetComponent<TransformComponent>()->position.y + offset.y;
	}

	void Update()
	{
		hitbox.x = entity->GetComponent<TransformComponent>()->position.x + offset.x;
        hitbox.y = entity->GetComponent<TransformComponent>()->position.y + offset.y;
	}
	
	void ProcessCollision(Entity* other)
	{
		// If this is a wall and the collision is with a player, it's possible that the player is a few units
		// into the wall. To counter this, I create 2 ghost rectangles that move opposite of the player's
		// velocity on the x and y axis, respectively. Whichever one stops colliding with this wall first is
		// the direction that the player is pushed to clear itself from collision.
		if (entity->name == "wall" && other->name == "player") {
			Rectangle otherHitbox = other->GetComponent<HitboxComponent>()->hitbox;		 	   
			float xDistanceToFree = 0;
			Vector2D velocity = other->GetComponent<TransformComponent>()->velocity;
			do {
				otherHitbox.x -= velocity.x;
				xDistanceToFree -= velocity.x;
			} while ((hitbox.x < otherHitbox.x + otherHitbox.w) &&
					 (hitbox.x + hitbox.w > otherHitbox.x) &&
					 (hitbox.y < otherHitbox.y + otherHitbox.h) &&
					 (hitbox.y + hitbox.h > otherHitbox.y) && velocity.x != 0);

			Rectangle otherHitbox2 = other->GetComponent<HitboxComponent>()->hitbox;
			float yDistanceToFree = 0;
			do {
				otherHitbox2.y -= velocity.y;
				yDistanceToFree -= velocity.y;
			} while ((hitbox.x < otherHitbox2.x + otherHitbox2.w) &&
                     (hitbox.x + hitbox.w > otherHitbox2.x) &&
                     (hitbox.y < otherHitbox2.y + otherHitbox2.h) &&
                     (hitbox.y + hitbox.h > otherHitbox2.y) && velocity.y != 0);
			
			if (std::abs(xDistanceToFree) < std::abs(yDistanceToFree) || yDistanceToFree == 0)
				other->GetComponent<TransformComponent>()->position.x += xDistanceToFree;
			else
				other->GetComponent<TransformComponent>()->position.y += yDistanceToFree;
		}
	}
};
