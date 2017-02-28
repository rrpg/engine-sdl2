#include "MoveUp.hpp"

void MoveUpCommand::execute(Actor *actor) {
	_execute(actor, actor->getX(), actor->getY() - 1);
}
