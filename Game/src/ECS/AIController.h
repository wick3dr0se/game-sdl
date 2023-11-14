#pragma once

#include "Components.h"
#include "ECS.h"

class AIController : public Component
{
public:
    TransformComponent* transform;
    SpriteComponent* sprite;
    Uint32 currentTime = SDL_GetTicks();
    int elapsedTime;

    AIController()
    {}

    ~AIController()
    {}

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();

        std::srand(std::time(0));
    }

    void update() override
    {
        int randomDirection = std::rand() % 4;

        elapsedTime = SDL_GetTicks() - currentTime;
        if (elapsedTime > 500)
        {
            switch (randomDirection)
            {
            case 0:
                transform->velocity.x = 0;
                transform->velocity.y = -1;
                sprite->Play("idle");
                break;
            case 1:
                transform->velocity.x = 0;
                transform->velocity.y = 1;
                sprite->Play("idle");
                break;
            case 2:
                transform->velocity.x = -1;
                transform->velocity.y = 0;
                sprite->Play("walk");
                sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                break;
            case 3:
                transform->velocity.x = 1;
                transform->velocity.y = 0;
                sprite->Play("walk");
                break;
            default:
                break;
            }

            currentTime = SDL_GetTicks();
        }
    }
};