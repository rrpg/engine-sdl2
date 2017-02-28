#include "Move.hpp"

void MoveCommand::_execute(Actor* actor, Map* map, int xDest, int yDest) {
	if (map->isCellWalkable(xDest, yDest)) {
		actor->setX(xDest);
		actor->setY(yDest);
	}
}
