#include "BehaviourMonster.hpp"
#include <iostream>

bool BehaviourMonster::update(Map *map, Actor *actor) {
	bool updated = false;
	std::cout << "actor " << actor << " updated in map " << map << std::endl;
	return updated;
}
