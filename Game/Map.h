#pragma once

#include "Game.h"

class Map
{
public:
    Map();
    ~Map();

    void LoadMap(int arr[15][20]);
    void DrawMap();
private:
    SDL_Rect src;
    SDL_Rect dest;

    SDL_Texture* grass;
    SDL_Texture* dirt;
    SDL_Texture* water;

    int map[15][20];
};