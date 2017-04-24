#include "Move.hpp"

bool MoveCommand::execute(Actor* actor, Map &map, unsigned int xDest, unsigned int yDest) {
	bool ret = false;
	if (map.isCellWalkable(xDest, yDest)) {
		map.moveActor(actor, xDest, yDest);
		ret = true;
	}

	return ret;
}
