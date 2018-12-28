#include "Systems.hpp"

TransformComponent::TransformComponent(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {};

RenderComponent::RenderComponent() {}
RenderComponent::RenderComponent(int r, int g, int b) : r(r), g(g), b(b) {};

PhysicsComponent::PhysicsComponent() {}
PhysicsComponent::PhysicsComponent(bool moving) : moving(moving) {};

RenderSystem::RenderSystem() { AddComponents<TransformComponent, RenderComponent>(); }
void RenderSystem::Update(double deltatime, std::vector<Entity*> entities)
{
    for (Entity* e : entities) {
        auto r = e->GetComponent<RenderComponent>();
        auto t = e->GetComponent<TransformComponent>();
        SDL_SetRenderDrawColor(renderer, r->r, r->g, r->b, 255);

        SDL_Rect rect;
        rect.x = (int)t->x;
        rect.y = (int)t->y;
        rect.w = (int)t->w;
        rect.h = (int)t->h;
        SDL_RenderFillRect(renderer, &rect);
    }
}

bool AABB(Entity* e1, Entity* e2)
{
    auto t1 = e1->GetComponent<TransformComponent>();
    auto t2 = e2->GetComponent<TransformComponent>();
    return ((int)t1->x < (t2->x + t2->w) &&
            (int)t2->x < (t1->x + t1->w) &&
            (int)t1->y < (t2->y + t2->h) &&
            (int)t2->y < (t1->y + t1->h));
}


PhysicsSystem::PhysicsSystem() { AddComponents<TransformComponent, PhysicsComponent>(); }
void PhysicsSystem::Update(double deltatime, std::vector<Entity*> entities)
{
 	for (Entity* e : entities) {
        auto trans = e->GetComponent<TransformComponent>();
        auto phys = e->GetComponent<PhysicsComponent>();

		// Apply gravity to moving objects
        if (phys->moving)
            phys->yvel -= gravity * deltatime;
		else continue;

        // X axis movement
        trans->x += phys->xvel;
        for (Entity* e2 : entities) {
            if (e == e2) continue;

            auto trans2 = e2->GetComponent<TransformComponent>();
            if (AABB(e, e2)) {
                if (phys->xvel > 0)
                    trans->x = trans2->x - trans->w;
                else if (phys->xvel < 0)
                    trans->x = trans2->x + trans2->w;
                phys->xvel = 0;
			}
        }

		// Y axis movement
        trans->y += phys->yvel;
        for (Entity* e2 : entities) {
            if (e == e2) continue;

            auto trans2 = e2->GetComponent<TransformComponent>();
            if (AABB(e, e2)) {
                if (phys->yvel > 0)
					trans->y = trans2->y - trans->h;
                else if (phys->yvel < 0)
                    trans->y = trans2->y + trans2->h;
                phys->yvel = 0;
            }
        }
    }
}
