#include "BehaviourPlayer.hpp"
#include "rRpg.hpp"
#include "Command/MoveUp.hpp"
#include "Command/MoveDown.hpp"
#include "Command/MoveLeft.hpp"
#include "Command/MoveRight.hpp"
#include "SDL2_framework/UserActions.h"
#include "SDL2_framework/ServiceProvider.h"

const uint32_t timeBetweenActions = 100;

bool BehaviourPlayer::update(rRpg *engine, Actor *actor) {
	bool updated = false;
	uint32_t currentTimestamp = SDL_GetTicks();
	if (currentTimestamp - m_iLastTimeActed <= timeBetweenActions) {
		return updated;
	}

	m_iLastTimeActed = currentTimestamp;
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
		updated = command->execute(actor, engine->getMap());
		free(command);
	}

	return updated;
}
