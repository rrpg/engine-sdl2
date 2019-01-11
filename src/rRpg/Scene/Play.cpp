#include "Play.hpp"
#include "Utils.hpp"
#include "GameOver.hpp"
#include "Actor.hpp"
#include "SDL2_framework/Game.h"
#include "SDL2_framework/ServiceProvider.h"

const std::string PlayScene::s_stateID = "PLAY";

PlayScene::PlayScene() : engine(rRpg()) {}

void PlayScene::update() {
	if (ServiceProvider::getUserActions()->getActionState("QUIT")) {
		Game::Instance()->quit();
		return;
	}

	engine.update();
	if (engine.getHero()->isDead()) {
		Game::Instance()->getStateMachine()->changeState(
			new GameOverScene()
		);
	}

	State::update();
}

void PlayScene::render() {
	engine.render();
	State::render();
}

bool PlayScene::onEnter() {
	bool ret = true;
	engine.setTilesFile(
		Game::Instance()->getBinaryPath() + "/../resources/floor-tiles.dat"
	);
	engine.setObjectsFile(
		Game::Instance()->getBinaryPath() + "/../resources/objects.dat"
	);
	ret &= engine.loadTaxonomy(
		Game::Instance()->getBinaryPath() + "/../resources/taxonomy.dat"
	);
	if (ret) {
		engine.initialiseHero();
		ret &= engine.loadStartMap();
	}
	return ret;
}

bool PlayScene::onExit() {
	return true;
}

std::string PlayScene::getStateID() const {
	return s_stateID;
}
