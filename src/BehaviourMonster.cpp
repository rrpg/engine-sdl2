#include "BehaviourMonster.hpp"
#include "Command/MoveUp.hpp"
#include "Command/MoveDown.hpp"
#include "Command/MoveLeft.hpp"
#include "Command/MoveRight.hpp"
#include "Command/Attack.hpp"
#include "rRpg.hpp"
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
			engine->getHero()->getX() - actor->getX(),
			engine->getHero()->getY() - actor->getY()
		);
	}
	else {
		_executeRandomMove(engine, actor);
	}
	return updated;
}

void BehaviourMonster::_executeMove(rRpg *engine, Actor *actor, const int x, const int y) {
	bool executed = false;
	MoveCommand *command = 0;
	if (y < 0) {
		command = new MoveUpCommand();
	}
	else if (y > 0) {
		command = new MoveDownCommand();
	}

	if (command != 0) {
		executed = command->execute(actor, engine->getMap());
		delete command;
		command = 0;
	}

	if (!executed) {
		if (x < 0) {
			command = new MoveLeftCommand();
		}
		else if (x > 0) {
			command = new MoveRightCommand();
		}
	}

	if (command != 0) {
		executed = command->execute(actor, engine->getMap());
		delete command;
	}

	if (!executed) {
		_executeRandomMove(engine, actor);
	}
}

void BehaviourMonster::_executeRandomMove(rRpg *engine, Actor *actor) {
	MoveCommand *command = 0;
	bool commandExecuted = false;
	int directions[4] = {0, 1, 2, 3};
	std::random_shuffle(directions, directions + 4);
	for (int direction = 3; !commandExecuted && direction--;) {
		switch (directions[direction]) {
			case 0:
				command = new MoveUpCommand();
				break;
			case 1:
				command = new MoveDownCommand();
				break;
			case 2:
				command = new MoveLeftCommand();
				break;
			default:
				command = new MoveRightCommand();
				break;
		}

		commandExecuted = command->execute(actor, engine->getMap());
		delete command;
	}
}
