#ifndef Game_h
#define Game_h
#define SDL_MAIN_HANDLED

#include "SDL2/SDL.h"
#include <iostream>

class Game {
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
private:
	int cnt = 0;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif