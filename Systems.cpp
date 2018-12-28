#include "Systems.hpp"

TransformComponent::TransformComponent(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {};

RenderComponent::RenderComponent() {}
RenderComponent::RenderComponent(int zlayer, int r, int g, int b) : zlayer(zlayer), r(r), g(g), b(b) {};

PhysicsComponent::PhysicsComponent() {}
PhysicsComponent::PhysicsComponent(bool moving) : moving(moving) {};

ControlComponent::ControlComponent(float speed) : speed(speed) {};

ControlSystem::ControlSystem() { AddComponents<PhysicsComponent, ControlComponent>(); }
void ControlSystem::Update(double deltatime, std::vector<Entity*> entities)
{
    for (Entity* e : entities) {
        auto p = e->GetComponent<PhysicsComponent>();
        float speed = e->GetComponent<ControlComponent>()->speed;

        // Set vertical speed
        if (KB.up && KB.down)
            p->yvel = 0;
        else if (KB.up)
            p->yvel = -speed;
        else if (KB.down)
            p->yvel = speed;
        else
            p->yvel = 0;

        // Set horizontal speed
        if (KB.left && KB.right)
            p->xvel = 0;
        else if (KB.left)
            p->xvel = -speed;
        else if (KB.right)
            p->xvel = speed;
        else
            p->xvel = 0;
    }
}

CameraSystem::CameraSystem() { AddComponents<TransformComponent, ControlComponent>(); }
void CameraSystem::Update(double deltatime, std::vector<Entity*> entities)
{
    for (Entity* e : entities) {
        auto t = e->GetComponent<TransformComponent>();

        // Centers the camera on the player
        Cam.x = (t->x + t->w/2) - (Cam.width/2);
        Cam.y = (t->y + t->h/2) - (Cam.height/2);
    }
}

RenderSystem::RenderSystem() { AddComponents<TransformComponent, RenderComponent>(); }
void RenderSystem::Update(double deltatime, std::vector<Entity*> entities)
{
    for (int i = 0; i < 3; i++)
        for (Entity* e : entities) {
            auto r = e->GetComponent<RenderComponent>();
            if (r->zlayer != i)
                continue;
            auto t = e->GetComponent<TransformComponent>();
            SDL_SetRenderDrawColor(renderer, r->r, r->g, r->b, 255);

            SDL_Rect rect;
            rect.x = (int)Cam.TransformX(t->x);
            rect.y = (int)Cam.TransformY(t->y);
            rect.w = (int)Cam.ScaleWidth(t->w);
            rect.h = (int)Cam.ScaleHeight(t->h);
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
