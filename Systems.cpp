#include "Systems.hpp"

TransformComponent::TransformComponent(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {};

RenderComponent::RenderComponent() {}
RenderComponent::RenderComponent(int zlayer, int r, int g, int b) : zlayer(zlayer), r(r), g(g), b(b) {};

CloudComponent::CloudComponent(float xvel, float yvel) : xvel(xvel), yvel(yvel) {};

AIComponent::AIComponent(Entity* player, float speed) : player(player), speed(speed) {};

PhysicsComponent::PhysicsComponent() {}
PhysicsComponent::PhysicsComponent(bool moving) : moving(moving) {};

PortalComponent::PortalComponent(Room* newroom, Room* room, Entity* player, bool* hit)
    : linkedRoom(newroom), currentRoom(room), player(player), hit(hit) {};

StairComponent::StairComponent(Room* room, Entity* player, bool* hit)
    : currentRoom(room), player(player), hit(hit) {};

ControlComponent::ControlComponent(float speed) : speed(speed) {};

ControlSystem::ControlSystem() { AddComponents<PhysicsComponent, ControlComponent>(); }
void ControlSystem::Update(double deltatime, std::vector<Entity*> entities)
{
    // For resets only
    if (startdelay > 0) {
        startdelay -= deltatime;
        return;
    }

    for (Entity* e : entities) {
        auto p = e->GetComponent<PhysicsComponent>();
        auto c = e->GetComponent<ControlComponent>();
        float speed = c->speed;

        // Set vertical speed, with a small acceleration period
        if (KB.up && !KB.down) {
            c->active = true;
            p->yvel -= drag*deltatime*speed;
            if (p->yvel < -speed) p->yvel = -speed;
        }
        else if (KB.down && !KB.up) {
            c->active = true;
            p->yvel += drag*deltatime*speed;
            if (p->yvel > speed) p->yvel = speed;
        }
        else {
            if (p->yvel > 0) {
                p->yvel -= drag*deltatime*speed;
                if (p->yvel < 0) p->yvel = 0;
            } else {
                p->yvel += drag*deltatime*speed;
                if (p->yvel > 0) p->yvel = 0;
            }
        }

        // Set horizontal speed
        if (KB.left && !KB.right) {
            c->active = true;
            p->xvel -= drag*deltatime*speed;
            if (p->xvel < -speed) p->xvel = -speed;
        }
        else if (KB.right && !KB.left) {
            c->active = true;
            p->xvel += drag*deltatime*speed;
            if (p->xvel > speed) p->xvel = speed;
        }
        else {
            if (p->xvel > 0) {
                p->xvel -= drag*deltatime*speed;
                if (p->xvel < 0) p->xvel = 0;
            } else {
                p->xvel += drag*deltatime*speed;
                if (p->xvel > 0) p->xvel = 0;
            }
        }
    }
}

AISystem::AISystem() { AddComponents<AIComponent, PhysicsComponent, TransformComponent>(); }
void AISystem::Update(double deltatime, std::vector<Entity*> entities)
{
    for (Entity* e : entities) {
        auto ai = e->GetComponent<AIComponent>();
        auto pt = ai->player->GetComponent<TransformComponent>();
        auto tt = e->GetComponent<TransformComponent>();
        auto phys = e->GetComponent<PhysicsComponent>();

        if (ai->player->GetComponent<ControlComponent>()->active) {
            if (tt->x > pt->x + pt->w) phys->xvel = -ai->speed;
            if (tt->x < pt->x - tt->w) phys->xvel = ai->speed;
            if (tt->y > pt->y + pt->h) phys->yvel = -ai->speed;
            if (tt->y < pt->y - tt->w) phys->yvel = ai->speed;
        }
    }
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
        trans->x += phys->xvel * deltatime;
        for (Entity* e2 : entities) {
            if (e == e2) continue;
            if (e->name == "enemy" && e2->name == "enemy") continue;
            if (e->name == "enemy" && e2->name == "player") continue;

            auto trans2 = e2->GetComponent<TransformComponent>();
            if (AABB(e, e2)) {
                if (e->name == "player" && e2->name == "enemy") {
                    e2->Destroy();
                    continue;
                }

                if (phys->xvel > 0)
                    trans->x = trans2->x - trans->w;
                else if (phys->xvel < 0)
                    trans->x = trans2->x + trans2->w;
                phys->xvel = 0;
            }
        }

        // Y axis movement
        trans->y += phys->yvel * deltatime;
        for (Entity* e2 : entities) {
            if (e == e2) continue;
            if (e->name == "enemy" && e2->name == "enemy") continue;
            if (e->name == "enemy" && e2->name == "player") continue;

            auto trans2 = e2->GetComponent<TransformComponent>();
            if (AABB(e, e2)) {
                if (e->name == "player" && e2->name == "enemy") {
                    e2->Destroy();
                    continue;
                }

                if (phys->yvel > 0)
                    trans->y = trans2->y - trans->h;
                else if (phys->yvel < 0)
                    trans->y = trans2->y + trans2->h;
                phys->yvel = 0;
            }
        }
    }
}

PortalSystem::PortalSystem() { AddComponents<PortalComponent, TransformComponent>(); }
void PortalSystem::Update(double deltatime, std::vector<Entity*> entities)
{
    for (Entity* e : entities) {
        auto portal = e->GetComponent<PortalComponent>();
        if (AABB(e, portal->player)) {
            *(portal->hit) = true;
            portal->currentRoom->parent->activeRoom = portal->linkedRoom;
        }
    }
}

StairSystem::StairSystem() { AddComponents<StairComponent, TransformComponent>(); }
void StairSystem::Update(double deltatime, std::vector<Entity*> entities)
{
    for (Entity* e : entities) {
        auto stair = e->GetComponent<StairComponent>();
        if (AABB(e, stair->player)) {
            *(stair->hit) = true;
            stair->currentRoom->parent->complete = true;
        }
    }
}

CloudSystem::CloudSystem() { AddComponents<TransformComponent, CloudComponent>(); }
void CloudSystem::Update(double deltatime, std::vector<Entity*> entities)
{
    for (Entity* e : entities) {
        auto c = e->GetComponent<CloudComponent>();
        auto t = e->GetComponent<TransformComponent>();

        t->x += c->xvel * deltatime;
        t->y += c->yvel * deltatime;

        if (t->x < -Cam.width/2-t->w) t->x = MAP_WIDTH*100 + Cam.width/2;
        if (t->y < -Cam.height/2-t->h) t->y = MAP_HEIGHT*100 + Cam.height/2;
        if (t->x > MAP_WIDTH*100 + Cam.width/2) t->x = -Cam.width/2-t->w;
        if (t->y > MAP_HEIGHT*100 + Cam.height/2) t->y = -Cam.height/2-t->h;
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
    // fade
    if (fadetime > 0) fadetime -= deltatime;
    if (fadetime < 0) fadetime = 0;
    int alpha = 255 - fadetime * 255;

    for (int i = 0; i < 4; i++)
        for (Entity* e : entities) {
            auto r = e->GetComponent<RenderComponent>();
            if (r->zlayer != i)
                continue;
            auto t = e->GetComponent<TransformComponent>();
            SDL_SetRenderDrawColor(renderer, r->r, r->g, r->b, alpha);

            SDL_Rect rect;
            rect.x = (int)Cam.TransformX(t->x);
            rect.y = (int)Cam.TransformY(t->y);
            rect.w = (int)Cam.ScaleWidth(t->w);
            rect.h = (int)Cam.ScaleHeight(t->h);
            SDL_RenderFillRect(renderer, &rect);

            if (e->name == "player") {
                SDL_SetRenderDrawColor(renderer, 247, 147, 26, alpha);
                SDL_Rect rect;
                rect.x = (int)Cam.TransformX(t->x+20);
                rect.y = (int)Cam.TransformY(t->y+20);
                rect.w = (int)Cam.ScaleWidth(t->w-40);
                rect.h = (int)Cam.ScaleHeight(t->h-40);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
}

bool AABB(Entity* e1, Entity* e2)
{
    auto t1 = e1->GetComponent<TransformComponent>();
    auto t2 = e2->GetComponent<TransformComponent>();
    if (t1 == nullptr || t2 == nullptr)
        return false;

    return ((int)t1->x < (t2->x + t2->w) &&
            (int)t2->x < (t1->x + t1->w) &&
            (int)t1->y < (t2->y + t2->h) &&
            (int)t2->y < (t1->y + t1->h));
}
