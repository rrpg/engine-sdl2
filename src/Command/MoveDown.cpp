#include "MoveDown.hpp"

void MoveDownCommand::execute(Actor *actor) {
	actor->setY(actor->getY() + 1);
}
