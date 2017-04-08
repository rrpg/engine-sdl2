#include "Play.hpp"
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
	ret &= engine.loadTaxonomy(
		Game::Instance()->getBinaryPath() + "/../resources/taxonomy.dat"
	);
	ret &= engine.loadMap(
		Game::Instance()->getBinaryPath() + "/../resources/terrains.dat"
	);
	ret &= engine.initialiseHero();
	return ret;
}

bool PlayState::onExit() {
	return true;
}

std::string PlayState::getStateID() const {
	return s_stateID;
}
