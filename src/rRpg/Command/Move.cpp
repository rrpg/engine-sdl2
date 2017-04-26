#include "Move.hpp"

bool MoveCommand::execute(Actor* actor, Map &map, int xDest, int yDest) {
	bool ret = false;
	if (map.isCellWalkable(xDest, yDest, WALKABLE_CONSTRAINT_ACTOR_IS_BLOCKING)) {
		map.moveActor(actor, xDest, yDest);
		ret = true;
	}

	return ret;
}
