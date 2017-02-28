#include "Move.hpp"

void MoveCommand::_execute(Actor* actor, int xDest, int yDest) {
	actor->setX(xDest);
	actor->setY(yDest);
}
