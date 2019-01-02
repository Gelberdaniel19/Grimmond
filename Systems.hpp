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

struct CloudComponent : public Component
{
    float xvel, yvel;
    CloudComponent(float xvel, float yvel);
};

struct AIComponent : public Component
{
    Entity* player;
    float speed = 1;
    AIComponent(Entity* player, float speed);
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

struct StairComponent : public Component
{
    bool* hit;
    Room* currentRoom;
    Entity* player;
    StairComponent(Room* currentRoom, Entity* player, bool* hit);
};

struct ControlComponent : public Component
{
    float speed;
    bool active = false;
    ControlComponent(float speed);
};

bool AABB(Entity* e1, Entity* e2);

struct ControlSystem : public System
{
    float drag = 10;
    double startdelay = 0.6;
    ControlSystem();
    void Update(double deltatime, std::vector<Entity*> entities);
};

struct AISystem : public System
{
    AISystem();
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

struct StairSystem : public System
{
    StairSystem();
    void Update(double deltatime, std::vector<Entity*> entities);
};

struct CloudSystem : public System
{
    CloudSystem();
    void Update(double deltatime, std::vector<Entity*> entities);
};

struct CameraSystem : public System
{
    CameraSystem();
    void Update(double deltatime, std::vector<Entity*> entities);
};

struct RenderSystem : public System
{
    float fadetime = 0.6;
    RenderSystem();
    void Update(double deltatime, std::vector<Entity*> entities);
};
