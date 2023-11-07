#include "Map.h"
#include "Game.h"
#include <fstream>

Map::Map()
{

}

Map::~Map()
{

}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
    char tile;
    std::fstream mapfile;
    mapfile.open(path);

    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            mapfile.get(tile);
            Game::AddTile(atoi(&tile), x * 32, y * 32);
            mapfile.ignore();
        }
    }

    mapfile.close();
}