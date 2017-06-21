#include "Player.hpp"
#include "rRpg.hpp"
#include "Actor.hpp"
#include "Map/Event.hpp"
#include "Command/Move.hpp"
#include "Command/Attack.hpp"
#include "SDL2_framework/UserActions.h"
#include "SDL2_framework/ServiceProvider.h"

const uint32_t timeBetweenActions = 100;

bool BehaviourPlayer::update(rRpg *engine, Actor *actor) {
	bool updated = false,
		directionPressed = false;
	uint32_t currentTimestamp = SDL_GetTicks();
	int xDest = actor->getX(),
		yDest = actor->getY();
	if (currentTimestamp - m_iLastTimeActed <= timeBetweenActions) {
		engine->block();
		return updated;
	}

	directionPressed = _isDirectionPressed(xDest, yDest);

	Map &map = engine->getMap();
	if (!directionPressed) {
		m_iLastTimeActed = 0;
	}
	else {
		m_iLastTimeActed = currentTimestamp;
		updated = _tryMove(actor, engine, xDest, yDest);
		if (!updated) {
			updated = _tryAttack(actor, map, xDest, yDest);
		}
	}

	if (!updated) {
		engine->block();
	}

	return updated;
}

bool BehaviourPlayer::_isDirectionPressed(int &x, int &y) {
	bool directionPressed = false;
	UserActions* userActions = ServiceProvider::getUserActions();
	if (userActions->getActionState("MOVE_PLAYER_UP")) {
		--y;
		directionPressed = true;
	}
	else if (userActions->getActionState("MOVE_PLAYER_DOWN")) {
		++y;
		directionPressed = true;
	}
	else if (userActions->getActionState("MOVE_PLAYER_LEFT")) {
		--x;
		directionPressed = true;
	}
	else if (userActions->getActionState("MOVE_PLAYER_RIGHT")) {
		++x;
		directionPressed = true;
	}

	return directionPressed;
}

bool BehaviourPlayer::_tryMove(Actor *actor, rRpg *engine, int x, int y) {
	MoveCommand command = MoveCommand();
	Map &map = engine->getMap();
	bool moved = command.execute(actor, map, x, y);
	if (moved && map.hasEvent(x, y)) {
		MapEvent event = MapEvent();
		event.execute(engine, map.getEvent(x, y));
	}

	return moved;
}

bool BehaviourPlayer::_tryAttack(Actor *actor, Map &map, int x, int y) {
	std::shared_ptr<Actor> target = map.getActorAt(x, y);
	if (target == NULL) {
		return false;
	}

	AttackCommand attack = AttackCommand();
	return attack.execute(actor, map, x, y);
}
