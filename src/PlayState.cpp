#include "PlayState.hpp"

const std::string PlayState::s_stateID = "PLAY";

void PlayState::update() {
	GameState::update();
}

void PlayState::render() {
	GameState::render();
}

bool PlayState::onEnter() {
	return true;
}

bool PlayState::onExit() {
	return true;
}

std::string PlayState::getStateID() const {
	return s_stateID;
}
