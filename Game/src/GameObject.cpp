#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texsheet, int x, int y)
{
    objTexture = TextureManager::LoadTexture(texsheet);

    xpos = x;
    ypos = y;
}

void GameObject::Update()
{
    xpos++;
    ypos++;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = 32;
    srcRect.h = 32;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}

void GameObject::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}