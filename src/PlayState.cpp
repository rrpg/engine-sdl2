#include "PlayState.hpp"
#include "SDL2_framework/Game.h"
#include "SDL2_framework/ServiceProvider.h"

const std::string PlayState::s_stateID = "PLAY";

PlayState::PlayState() : engine(rRpg()) {}

void PlayState::update() {
	if (ServiceProvider::getUserActions()->getActionState("QUIT")) {
		Game::Instance()->quit();
		return;
	}

	engine.update();
	GameState::update();
}

void PlayState::render() {
	engine.render();
	GameState::render();
}

bool PlayState::onEnter() {
	engine.loadMap(
		Game::Instance()->getBinaryPath() + "/../resources/map1.map"
	);
	engine.loadTaxonomy(
		Game::Instance()->getBinaryPath() + "/../resources/taxonomy.dat"
	);
	engine.initialiseHero();
	return true;
}

bool PlayState::onExit() {
	return true;
}

std::string PlayState::getStateID() const {
	return s_stateID;
}
