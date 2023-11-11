#include "src/Game.h"

Game* game = nullptr;

int main()
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("Our new game!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, NULL, NULL, true);

    while (game->running())
    {
        frameStart = SDL_GetTicks();

        game->preRender();
        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();

    return 0;
}