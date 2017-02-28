#include "MoveDown.hpp"

void MoveDownCommand::execute(Actor *actor) {
	_execute(actor, actor->getX(), actor->getY() + 1);
}
