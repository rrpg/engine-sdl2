#include "BehaviourMonster.hpp"
#include "Command/MoveDown.hpp"
#include "rRpg.hpp"
#include <iostream>

bool BehaviourMonster::update(rRpg *engine, Actor *actor) {
	bool updated = true;
	MoveDownCommand c = MoveDownCommand();
	c.execute(actor, engine->getMap());
	return updated;
}
