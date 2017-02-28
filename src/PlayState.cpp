#include "PlayState.hpp"
#include "SDL2_framework/Game.h"
#include "SDL2_framework/UserActions.h"
#include "SDL2_framework/ServiceProvider.h"

const std::string PlayState::s_stateID = "PLAY";

PlayState::PlayState() : engine(rRpg()) {}

void PlayState::update() {
	UserActions* userActions = ServiceProvider::getUserActions();
	if (userActions->getActionState("MOVE_PLAYER_UP")) {
		engine.getHero()->setY(engine.getHero()->getY() - 1);
	}
	else if (userActions->getActionState("MOVE_PLAYER_DOWN")) {
		engine.getHero()->setY(engine.getHero()->getY() + 1);
	}
	else if (userActions->getActionState("MOVE_PLAYER_LEFT")) {
		engine.getHero()->setX(engine.getHero()->getX() - 1);
	}
	else if (userActions->getActionState("MOVE_PLAYER_RIGHT")) {
		engine.getHero()->setX(engine.getHero()->getX() + 1);
	}
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
