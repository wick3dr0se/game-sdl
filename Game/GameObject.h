#pragma once

#include "Game.h"

class GameObject {
public:
	GameObject(const char* texsheet, int x, int y);
	~GameObject();

	void Update();
	void Render();
private:
	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};