#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include "globals.hpp"
#include "types.hpp"
#include "Utils.hpp"
#include "SDL2_framework/Game.h"
#include "State/Play.hpp"
#include "ResourceManager.hpp"
#include <libgen.h>

const int FPS = 60;
const int DELAY_TIME = 1000 / FPS;

void _prepareTilesets(std::string binaryPath);

int main(int argc, char* args[]) {
	time_t t;
	srand((unsigned int) time(&t));
	Game* g;
	char buffer[1024];
	std::string binaryPath;
	Uint32 frameStart, frameTime;

	Utils::createFolder(Utils::getDataPath().c_str());

	realpath(dirname(args[argc - argc]), buffer);
	binaryPath = buffer;
	g = Game::Instance();
	g->setBinaryPath(binaryPath);
	if (!g->init("rRpg", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, FULL_SCREEN)) {
		Game::freeGame();
		return 1;
	}

	_prepareTilesets(binaryPath);
	g->getStateMachine()->changeState(new PlayState());
	while (g->isRunning()) {
		frameStart = SDL_GetTicks();
		InputUpdateResult result = g->handleEvents();
		if (result == HAS_EVENT) {
			g->update();
		}
		g->render();

		// use a delay to cap the fps
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME) {
			SDL_Delay(DELAY_TIME - frameTime);
		}
	}

	Game::freeGame();

	return 0;
}

void _prepareTilesets(std::string binaryPath) {
	ResourceManager<S_TilesetMapping> resourceManager;
	resourceManager.setResourceFile(binaryPath + "/../resources/tilesets.dat");
	resourceManager.parseBinaryFile();
	for (auto tileset : resourceManager.getParsedResources()) {
		std::cout << "Resource found: "
			<< tileset.second.tileset
			<< " (" << tileset.second.filePath << ")\n";
		TextureManager::Instance()->addTexture(
			binaryPath + "/../resources/" + tileset.second.filePath,
			tileset.second.tileset
		);
	}
}
