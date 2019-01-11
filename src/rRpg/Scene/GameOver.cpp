#include "GameOver.hpp"
#include "SDL2_framework/Game.h"
#include "SDL2_framework/ServiceProvider.h"

const std::string GameOverScene::s_stateID = "GAME_OVER";

void GameOverScene::update() {
	if (ServiceProvider::getUserActions()->getActionState("QUIT")) {
		Game::Instance()->quit();
		return;
	}
}

void GameOverScene::render() {
}

bool GameOverScene::onEnter() {
	bool ret = true;
	return ret;
}

bool GameOverScene::onExit() {
	return true;
}

std::string GameOverScene::getStateID() const {
	return s_stateID;
}
