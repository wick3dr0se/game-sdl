#include "Map.h"
#include "TextureManager.h"

int lvl1[15][20] = {
             { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
             { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
             { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
             { 0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0 },
             { 0,0,1,1,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0 },
             { 0,0,1,1,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0 },
             { 0,0,1,1,2,2,2,2,2,2,1,0,0,0,0,1,1,0,0,0 },
             { 0,0,0,1,2,2,2,2,2,2,1,0,0,0,1,1,1,0,0,0 },
             { 0,0,0,1,2,2,2,2,2,2,1,0,0,0,1,1,1,0,0,0 },
             { 0,0,1,1,1,1,1,2,2,2,1,0,0,0,1,1,1,0,0,0 },
             { 0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1 },
             { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1 },
             { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
             { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
             { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};

Map::Map()
{
    grass = TextureManager::LoadTexture("assets/grass.bmp");
    dirt = TextureManager::LoadTexture("assets/dirt.bmp");
    water = TextureManager::LoadTexture("assets/water.bmp");

    LoadMap(lvl1);

    src.x = 0;
    src.y = 0;
    src.w = 32;
    src.h = 32;

    dest.x = 0;
    dest.y = 0;
    dest.w = 32;
    dest.h = 32;
}

Map::~Map()
{
    SDL_DestroyTexture(grass);
    SDL_DestroyTexture(dirt);
    SDL_DestroyTexture(water);
}

void Map::LoadMap(int arr[15][20])
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            map[i][j] = arr[i][j];
        }
    }
}

void Map::DrawMap()
{
    int type = 0;

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            type = map[i][j];

            dest.x = j * 32;
            dest.y = i * 32;

            switch (type)
            {
            case 0:
                TextureManager::Draw(grass, src, dest);
                break;
            case 1:
                TextureManager::Draw(dirt, src, dest);
                break;
            case 2:
                TextureManager::Draw(water, src, dest);
                break;
            default:
                break;
            }
        }
    }
}