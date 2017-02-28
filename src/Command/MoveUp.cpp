#include "MoveUp.hpp"

void MoveUpCommand::execute(Actor *actor, Map *map) {
	_execute(actor, map, actor->getX(), actor->getY() - 1);
}
