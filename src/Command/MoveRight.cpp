#include "MoveRight.hpp"

void MoveRightCommand::execute(Actor *actor, Map *map) {
	_execute(actor, map, actor->getX() + 1, actor->getY());
}
