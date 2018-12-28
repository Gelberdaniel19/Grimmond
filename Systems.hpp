#pragma once
#include "globals.hpp"
#include "ECS.hpp"
#include "Room.hpp"

class Room;

struct TransformComponent : public Component
{
    float x, y, w, h;
    TransformComponent(float x, float y, float w, float h);
};

struct RenderComponent : public Component
{
    int r = 255;
    int g = 0;
    int b = 0;
    int zlayer = 0;
    RenderComponent();
    RenderComponent(int zlayer, int r, int g, int b);
};

struct PhysicsComponent : public Component
{
	bool moving = true;
    float xvel = 0;
    float yvel = 0;
    PhysicsComponent();
    PhysicsComponent(bool moving);
};

struct PortalComponent : public Component
{
    bool* hit;
    Room* linkedRoom;
    Room* currentRoom;
    Entity* player;
    PortalComponent(Room* linkedRoom, Room* currentRoom, Entity* player, bool* hit);
};

struct ControlComponent : public Component
{
    float speed;
    ControlComponent(float speed);
};

bool AABB(Entity* e1, Entity* e2);

struct ControlSystem : public System
{
    float drag = 10;
    ControlSystem();
    void Update(double deltatime, std::vector<Entity*> entities);
};

struct PhysicsSystem : public System
{
	float gravity = 0.01;
    PhysicsSystem();
    void Update(double deltatime, std::vector<Entity*> entities);
};

struct PortalSystem : public System
{
    PortalSystem();
    void Update(double deltatime, std::vector<Entity*> entities);
};

struct CameraSystem : public System
{
    CameraSystem();
    void Update(double deltatime, std::vector<Entity*> entities);
};

struct RenderSystem : public System
{
    RenderSystem();
    void Update(double deltatime, std::vector<Entity*> entities);
};
