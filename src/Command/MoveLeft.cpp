#include "MoveLeft.hpp"

void MoveLeftCommand::execute(Actor *actor) {
	actor->setX(actor->getX() - 1);
}
