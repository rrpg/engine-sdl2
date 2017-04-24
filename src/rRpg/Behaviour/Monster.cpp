#include <limits.h>
#include "Monster.hpp"
#include "../Command/Move.hpp"
#include "../Command/Attack.hpp"
#include "../rRpg.hpp"
#include <math.h>
#include <algorithm>

bool BehaviourMonster::update(rRpg *engine, Actor *actor) {
	bool updated = true;
	if (actor->isNextTo(engine->getHero())) {
		AttackCommand command = AttackCommand();
		command.execute(
			actor,
			engine->getMap(),
			engine->getHero()->getX(),
			engine->getHero()->getY()
		);
	}
	else if (actor->seesActor(engine->getMap(), engine->getHero())) {
		_executeMove(
			engine,
			actor,
			engine->getHero()->getX(),
			engine->getHero()->getY()
		);
	}
	else {
		_executeRandomMove(engine, actor);
	}
	return updated;
}

void BehaviourMonster::_executeMove(rRpg *engine, Actor *actor, const unsigned int xTarget, const unsigned int yTarget) {
	bool executed = false;
	unsigned int xActor = actor->getX(),
		yActor = actor->getY(),
		xDest = xActor,
		yDest = yActor;
	MoveCommand command = MoveCommand();

	// larger Y, move vertically to close the distance
	if (std::abs(xActor - xTarget) < std::abs(yActor - yTarget)) {
		// instead of doint -1 (which asks for a cast)
		yDest += (yActor < yTarget) ? UINT_MAX : 1;
	}
	// larger X, move horizontally to close the distance
	else {
		// instead of doint -1 (which asks for a cast)
		xDest += (xActor < xTarget) ? UINT_MAX : 1;
	}

	executed = command.execute(actor, engine->getMap(), xDest, yDest);

	if (!executed) {
		_executeRandomMove(engine, actor);
	}
}

void BehaviourMonster::_executeRandomMove(rRpg *engine, Actor *actor) {
	MoveCommand command = MoveCommand();
	bool commandExecuted = false;
	unsigned int directions[4] = {0, 1, 2, 3},
		xDest = actor->getX(),
		yDest = actor->getY();
	std::random_shuffle(directions, directions + 4);
	for (int direction = 3; !commandExecuted && direction--;) {
		switch (directions[direction]) {
			case 0:
				--yDest;
				break;
			case 1:
				++yDest;
				break;
			case 2:
				--xDest;
				break;
			default:
				++xDest;
				break;
		}

		commandExecuted = command.execute(actor, engine->getMap(), xDest, yDest);
	}
}
