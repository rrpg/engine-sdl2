#include "Attack.hpp"

bool AttackCommand::execute(Actor* actor, Map &map, unsigned int xDest, unsigned int yDest) {
	Actor *target = map.getActorAt(xDest, yDest);
	if (target == NULL) {
		return false;
	}

	actor->attack(target);
	return true;
}
