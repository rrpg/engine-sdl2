#include "MoveLeft.hpp"

void MoveLeftCommand::execute(Actor *actor, Map *map) {
	_execute(actor, map, actor->getX() - 1, actor->getY());
}
