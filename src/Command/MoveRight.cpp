#include "MoveRight.hpp"

bool MoveRightCommand::execute(Actor *actor, Map &map) {
	return _execute(actor, map, actor->getX() + 1, actor->getY());
}
