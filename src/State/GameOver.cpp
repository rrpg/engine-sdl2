#include "GameOver.hpp"
#include "SDL2_framework/Game.h"
#include "SDL2_framework/ServiceProvider.h"

const std::string GameOverState::s_stateID = "GAME_OVER";

void GameOverState::update() {
	if (ServiceProvider::getUserActions()->getActionState("QUIT")) {
		Game::Instance()->quit();
		return;
	}
}

void GameOverState::render() {
}

bool GameOverState::onEnter() {
	bool ret = true;
	return ret;
}

bool GameOverState::onExit() {
	return true;
}

std::string GameOverState::getStateID() const {
	return s_stateID;
}
