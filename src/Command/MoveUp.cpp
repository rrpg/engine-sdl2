#include "MoveUp.hpp"

void MoveUpCommand::execute(Actor *actor) {
	actor->setY(actor->getY() - 1);
}
