#include "MoveRight.hpp"

bool MoveRightCommand::execute(Actor *actor, Map &map) {
	return MoveCommand::execute(actor, map, actor->getX() + 1, actor->getY());
}
