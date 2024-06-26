#pragma once

#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{
public:
    Vector2D position;
    Vector2D velocity;

    int width = 32;
    int height = 32;
    int scale = 1;
    int speed = 3;

    TransformComponent()
    {
        position.Zero();
    }

    TransformComponent(int sc)
    {
        position.x = 400;
        position.y = 320;
        scale = sc;
    }

    TransformComponent(float x, float y)
    {
        position.Zero();
    }

    TransformComponent(float x, float y, int w, int h, int sc)
    {
        position.x = x;
        position.y = y;
        width = w;
        height = h;
        scale = sc;
    }

    void init() override
    {
        velocity.Zero();
    }

    void update() override
    {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};