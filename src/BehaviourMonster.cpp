#include "BehaviourMonster.hpp"
#include "rRpg.hpp"
#include <iostream>

bool BehaviourMonster::update(rRpg *engine, Actor *actor) {
	bool updated = true;
	std::cout << "actor " << actor << " updated in engine->getMap() " << engine->getMap() << std::endl;
	return updated;
}
