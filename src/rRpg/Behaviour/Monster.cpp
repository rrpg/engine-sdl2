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

void BehaviourMonster::_executeMove(rRpg *engine, Actor *actor, const int xTarget, const int yTarget) {
	bool executed = false;
	int xActor = actor->getX(),
		yActor = actor->getY(),
		xDest = xActor,
		yDest = yActor;
	MoveCommand command = MoveCommand();

	// larger Y, move vertically to close the distance
	if (std::abs(xActor - xTarget) < std::abs(yActor - yTarget)) {
		if (yActor < yTarget) {
			++yDest;
		}
		else {
			--yDest;
		}
		executed = command.execute(actor, engine->getMap(), xDest, yDest);
		yDest = yActor;
	}

	// larger X or could not move vertically, move horizontally to close the
	// distance
	if (!executed) {
		if (xActor < xTarget) {
			++xDest;
		}
		else {
			--xDest;
		}
		executed = command.execute(actor, engine->getMap(), xDest, yDest);
	}

	// If could not move towards the player, then move randomly
	if (!executed) {
		_executeRandomMove(engine, actor);
	}
}

void BehaviourMonster::_executeRandomMove(rRpg *engine, Actor *actor) {
	MoveCommand command = MoveCommand();
	bool commandExecuted = false;
	int directions[4] = {0, 1, 2, 3},
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
