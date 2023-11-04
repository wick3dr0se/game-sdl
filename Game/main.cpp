#include "Game.h"

Game* game = nullptr;

int main()
{
	game = new Game();

	game->init("Our new game!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, false);

	while (game->running())
	{
		game->preRender();
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}