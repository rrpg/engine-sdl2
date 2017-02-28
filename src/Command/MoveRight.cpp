#include "MoveRight.hpp"

void MoveRightCommand::execute(Actor *actor) {
	_execute(actor, actor->getX() + 1, actor->getY());
}
