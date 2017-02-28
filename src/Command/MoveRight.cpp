#include "MoveRight.hpp"

void MoveRightCommand::execute(Actor *actor) {
	actor->setX(actor->getX() + 1);
}
