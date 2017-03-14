#include "MoveLeft.hpp"

bool MoveLeftCommand::execute(Actor *actor, Map &map) {
	return MoveCommand::execute(actor, map, actor->getX() - 1, actor->getY());
}
