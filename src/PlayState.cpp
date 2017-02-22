#include "PlayState.hpp"

const std::string PlayState::s_stateID = "PLAY";

PlayState::PlayState() : engine(rRpg()) {}

void PlayState::update() {
	GameState::update();
}

void PlayState::render() {
	GameState::render();
}

bool PlayState::onEnter() {
	engine = rRpg();
	return true;
}

bool PlayState::onExit() {
	return true;
}

std::string PlayState::getStateID() const {
	return s_stateID;
}
