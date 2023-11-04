#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture, SDL_Renderer* ren)
{
	SDL_Surface* tmpSurface = SDL_LoadBMP(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return tex;
}