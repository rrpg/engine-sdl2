#include "BehaviourMonster.hpp"
#include "Command/MoveUp.hpp"
#include "Command/MoveDown.hpp"
#include "Command/MoveLeft.hpp"
#include "Command/MoveRight.hpp"
#include "rRpg.hpp"
#include <math.h>
#include <algorithm>

bool BehaviourMonster::update(rRpg *engine, Actor *actor) {
	bool updated = true;
	if (!actor->isNextTo(engine->getHero())
		&& actor->seesActor(engine->getMap(), engine->getHero())
	) {
		_executeMove(
			engine,
			actor,
			engine->getHero()->getX() - actor->getX(),
			engine->getHero()->getY() - actor->getY()
		);
	}
	return updated;
}

void BehaviourMonster::_executeMove(rRpg *engine, Actor *actor, const int x, const int y) {
	bool executed = false;
	Command *command = 0;
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
}
