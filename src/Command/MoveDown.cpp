#include "MoveDown.hpp"

void MoveDownCommand::execute(Actor *actor, Map *map) {
	_execute(actor, map, actor->getX(), actor->getY() + 1);
}
