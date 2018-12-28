#pragma once
#include "globals.hpp"
#include "ECS.hpp"

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
    RenderComponent();
    RenderComponent(int r, int g, int b);
};

struct PhysicsComponent : public Component
{
	bool moving = true;
    float xvel = 0;
    float yvel = 0;
    PhysicsComponent();
    PhysicsComponent(bool moving);
};

bool AABB(Entity* e1, Entity* e2);

struct RenderSystem : public System
{
    RenderSystem();
    void Update(double deltatime, std::vector<Entity*> entities);
};

struct PhysicsSystem : public System
{
	float gravity = 0.01;
    PhysicsSystem();
    void Update(double deltatime, std::vector<Entity*> entities);
};
