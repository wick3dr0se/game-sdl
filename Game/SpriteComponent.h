#pragma once

#include "SDL2/SDL.h"
#include "Components.h"

class SpriteComponent : public Component
{
public:
    SpriteComponent() = default;
    SpriteComponent(const char* path)
    {
        setTex(path);
    }

    void setTex(const char* path)
    {
        texture = TextureManager::LoadTexture(path);
    }

    void init() override
    {
        position = &entity->getComponent<PositionComponent>();

        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = 32;
        srcRect.h = 32;

        destRect.w = 32;
        destRect.h = 32;
    }

    void update() override
    {
        destRect.x = position->x();
        destRect.y = position->y();
    }

    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect);
    }
private:
    PositionComponent* position;
    SDL_Texture* texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;
};