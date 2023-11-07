#ifndef Game_h
#define Game_h
#define SDL_MAIN_HANDLED

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <vector>

class ColliderComponent;

class Game
{
public:
    Game();
    ~Game();

    void init(const char* title, int x, int y, int w, int h, bool fullscreen);
    void preRender();
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() { return isRunning; }

    static void AddTile(int id, int x, int y);
    static SDL_Renderer* renderer;
    static SDL_Event event;
    static std::vector<ColliderComponent*> colliders;
private:
    int cnt = 0;
    bool isRunning = false;
    SDL_Window* window;
};

#endif