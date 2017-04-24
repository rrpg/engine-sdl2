#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdlib.h>
#include "SDL2_framework/Game.h"
#include "State/Play.hpp"
#include "Parser/Resource.hpp"
#include <libgen.h>

const int FPS = 60;
const int DELAY_TIME = 1000 / FPS;

int main(int argc, char* args[]) {
	time_t t;
	srand((unsigned) time(&t));
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

	ResourceParser parser = ResourceParser();
	std::string tilesetsPath = binaryPath + "/../resources/tilesets.dat";
	parser.parseFile(tilesetsPath.c_str());
	g->getStateMachine()->changeState(new PlayState());
	while (g->isRunning()) {
		frameStart = SDL_GetTicks();
		g->handleEvents();
		g->update();
		g->render();

		// use a delay to cap the fps
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME) {
			SDL_Delay((unsigned int) (DELAY_TIME - frameTime));
		}
	}

	Game::freeGame();

	return 0;
}
