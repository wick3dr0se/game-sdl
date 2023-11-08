#pragma once

#include "SDL2/SDL.h"
#include "ECS.h"

class TileComponent : public Component
{
public:
    SDL_Texture* texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;

    TileComponent() = default;

    ~TileComponent()
    {
        SDL_DestroyTexture(texture);
    }

    TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path)
    {
        texture = TextureManager::LoadTexture(path);

        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = 32;
        srcRect.h = 32;

        destRect.x = xpos;
        destRect.y = ypos;
        destRect.w = 64;
        destRect.h = 64;
    }

    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};