#include "Game.hpp"

Game* game = nullptr;

int main()
{
	game = new Game();

	game->init("Our new game!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, false);

	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}