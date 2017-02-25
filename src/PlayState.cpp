#include "PlayState.hpp"
#include "SDL2_framework/Game.h"

const std::string PlayState::s_stateID = "PLAY";

PlayState::PlayState() : engine(rRpg()) {}

void PlayState::update() {
	engine.update();
	GameState::update();
}

void PlayState::render() {
	engine.render();
	GameState::render();
}

bool PlayState::onEnter() {
	engine = rRpg();
	engine.loadMap(
		Game::Instance()->getBinaryPath() + "/../resources/map1.map"
	);
	return true;
}

bool PlayState::onExit() {
	return true;
}

std::string PlayState::getStateID() const {
	return s_stateID;
}
