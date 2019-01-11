#include "Play.hpp"
#include "Utils.hpp"
#include "GameOver.hpp"
#include "Actor.hpp"
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

	State::update();
}

void PlayState::render() {
	engine.render();
	State::render();
}

bool PlayState::onEnter() {
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

bool PlayState::onExit() {
	return true;
}

std::string PlayState::getStateID() const {
	return s_stateID;
}
