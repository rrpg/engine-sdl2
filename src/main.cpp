#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdlib.h>
#include "SDL2_framework/Game.h"
#include "PlayState.hpp"
#include <libgen.h>

const int FPS = 25;
const int DELAY_TIME = 1000 / FPS;

int main(int argc, char* args[]) {
	Game* g;
	bool fullScreen = false;
	char buffer[1024];
	std::string binaryPath;
	Uint32 frameStart, frameTime;

	realpath(dirname(args[argc - argc]), buffer);
	binaryPath = buffer;
	g = Game::Instance();
	g->setBinaryPath(binaryPath);
	if (!g->init("rRpg", 100, 100, 640, 480, fullScreen)) {
		Game::freeGame();
		return 1;
	}

	g->getStateMachine()->changeState(new PlayState());
	while (g->isRunning()) {
		frameStart = SDL_GetTicks();
		g->handleEvents();
		g->update();
		g->render();

		// use a delay to cap the fps
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime< DELAY_TIME) {
			SDL_Delay((int) (DELAY_TIME - frameTime));
		}
	}

	Game::freeGame();

	return 0;
}
