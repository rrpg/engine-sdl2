#include "BehaviourMonster.hpp"
#include "Command/MoveDown.hpp"
#include "rRpg.hpp"
#include <iostream>
#include <math.h>

bool BehaviourMonster::update(rRpg *engine, Actor *actor) {
	bool updated = true;
	if (actor->seesActor(engine->getMap(), engine->getHero())) {
		std::cout << actor << " sees player\n";
	}
	return updated;
}

