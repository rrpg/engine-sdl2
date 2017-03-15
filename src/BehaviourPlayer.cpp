#include "BehaviourPlayer.hpp"
#include "rRpg.hpp"
#include "Command/Move.hpp"
#include "Command/Attack.hpp"
#include "SDL2_framework/UserActions.h"
#include "SDL2_framework/ServiceProvider.h"

const uint32_t timeBetweenActions = 100;

bool BehaviourPlayer::update(rRpg *engine, Actor *actor) {
	bool updated = false,
		 moves = false;
	uint32_t currentTimestamp = SDL_GetTicks();
	int xDest = actor->getX(),
		yDest = actor->getY();
	if (currentTimestamp - m_iLastTimeActed <= timeBetweenActions) {
		engine->block();
		return updated;
	}

	UserActions* userActions = ServiceProvider::getUserActions();
	MoveCommand command = MoveCommand();
	if (userActions->getActionState("MOVE_PLAYER_UP")) {
		--yDest;
		moves = true;
	}
	else if (userActions->getActionState("MOVE_PLAYER_DOWN")) {
		++yDest;
		moves = true;
	}
	else if (userActions->getActionState("MOVE_PLAYER_LEFT")) {
		--xDest;
		moves = true;
	}
	else if (userActions->getActionState("MOVE_PLAYER_RIGHT")) {
		++xDest;
		moves = true;
	}

	if (moves) {
		m_iLastTimeActed = currentTimestamp;
		updated = command.execute(actor, engine->getMap(), xDest, yDest);
		if (!updated) {
			Actor *target = engine->getMap().getActorAt(xDest, yDest);
			if (target != NULL) {
				AttackCommand attack = AttackCommand();
				updated = attack.execute(actor, engine->getMap(), xDest, yDest);
			}
		}
	}
	else {
		m_iLastTimeActed = 0;
	}

	if (!updated) {
		engine->block();
	}

	return updated;
}
