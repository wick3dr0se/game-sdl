#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
    TransformComponent* transform;
    SpriteComponent* sprite;
    Vector2D lastPos;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override
    {
        if (Game::event.type == SDL_KEYDOWN)
        {
            lastPos = transform->position;

            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                transform->velocity.y = -1;
                sprite->Play("idle");
                break;
            case SDLK_a:
                transform->velocity.x = -1;
                sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                sprite->Play("walk");
                break;
            case SDLK_d:
                transform->velocity.x = 1;
                sprite->spriteFlip = SDL_FLIP_NONE;
                sprite->Play("walk");
                break;
            case SDLK_s:
                transform->velocity.y = 1;
                sprite->Play("idle");
                break;
            case SDLK_SPACE:
                Game::assets->CreateProjectile(transform->position, Vector2D(2, 0), 3, 2);
                break;
            default:
                break;
            }
        }

        if (Game::event.type == SDL_KEYUP)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
            case SDLK_a:
            case SDLK_d:
            case SDLK_s:
                transform->velocity = { 0, 0 };
                sprite->Play("idle");
                break;
            default:
                break;
            }
        }

        if (std::abs(transform->position.x - lastPos.x) >= transform->scale * 32 ||
            std::abs(transform->position.y - lastPos.y) >= transform->scale * 32)
        {
            transform->velocity = { 0, 0 };
            sprite->Play("idle");
        }
    }
};