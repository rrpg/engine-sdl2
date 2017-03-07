#include "Move.hpp"

bool MoveCommand::_execute(Actor* actor, Map &map, int xDest, int yDest) {
	bool ret = false;
	if (map.isCellWalkable(xDest, yDest)) {
		map.moveActor(actor, xDest, yDest);
		ret = true;
	}

	return ret;
}
