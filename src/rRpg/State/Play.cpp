#include "Play.hpp"
#include "Utils.hpp"
#include "GameOver.hpp"
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
	if (engine.getHero()->isDead()) {
		Game::Instance()->getStateMachine()->changeState(
			new GameOverState()
		);
	}

	GameState::update();
}

void PlayState::render() {
	engine.render();
	GameState::render();
}

bool PlayState::onEnter() {
	bool ret = true;
	engine.setTilesFile(
		Game::Instance()->getBinaryPath() + "/../resources/floor-tiles.dat"
	);
	ret &= engine.loadTaxonomy(
		Game::Instance()->getBinaryPath() + "/../resources/taxonomy.dat"
	);
	if (ret) {
		engine.initialiseHero();
		ret &= engine.loadMap("cave1", 0);
	}
	return ret;
}

bool PlayState::onExit() {
	return true;
}

std::string PlayState::getStateID() const {
	return s_stateID;
}
