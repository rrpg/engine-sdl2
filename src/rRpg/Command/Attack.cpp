#include "Attack.hpp"
#include "Map.hpp"
#include "Actor.hpp"
#include <memory>

bool AttackCommand::execute(Actor* actor, Map &map, int xDest, int yDest) {
	std::shared_ptr<Actor> target = map.getActorAt(xDest, yDest);
	if (target == NULL) {
		return false;
	}

	actor->attack(target);
	return true;
}
