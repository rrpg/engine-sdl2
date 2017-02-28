#include "MoveLeft.hpp"

void MoveLeftCommand::execute(Actor *actor) {
	_execute(actor, actor->getX() - 1, actor->getY());
}
