#include "PlayState.hpp"
#include "SDL2_framework/Game.h"
#include "SDL2_framework/UserActions.h"
#include "SDL2_framework/ServiceProvider.h"
#include "Command/MoveUp.hpp"
#include "Command/MoveDown.hpp"
#include "Command/MoveLeft.hpp"
#include "Command/MoveRight.hpp"

const std::string PlayState::s_stateID = "PLAY";
const uint32_t timeBetweenActions = 100;

PlayState::PlayState() : engine(rRpg()) {}

void PlayState::update() {
	UserActions* userActions = ServiceProvider::getUserActions();
	Command *command = 0;
	if (userActions->getActionState("MOVE_PLAYER_UP")) {
		command = new MoveUpCommand();
	}
	else if (userActions->getActionState("MOVE_PLAYER_DOWN")) {
		command = new MoveDownCommand();
	}
	else if (userActions->getActionState("MOVE_PLAYER_LEFT")) {
		command = new MoveLeftCommand();
	}
	else if (userActions->getActionState("MOVE_PLAYER_RIGHT")) {
		command = new MoveRightCommand();
	}

	if (command != 0) {
		uint32_t currentTimestamp = SDL_GetTicks();
		if (currentTimestamp - m_iTimestampLastCommand > timeBetweenActions) {
			command->execute(engine.getHero(), engine.getMap());
			m_iTimestampLastCommand = currentTimestamp;
		}
		free(command);
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
