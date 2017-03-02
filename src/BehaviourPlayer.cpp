#include "BehaviourPlayer.hpp"
#include "Command/MoveUp.hpp"
#include "Command/MoveDown.hpp"
#include "Command/MoveLeft.hpp"
#include "Command/MoveRight.hpp"
#include "SDL2_framework/UserActions.h"
#include "SDL2_framework/ServiceProvider.h"

bool BehaviourPlayer::update(Map *map, Actor *actor) {
	bool updated = false;
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
		updated = command->execute(actor, map);
		free(command);
	}

	return updated;
}
