#include "MoveUp.hpp"

bool MoveUpCommand::execute(Actor *actor, Map &map) {
	return MoveCommand::execute(actor, map, actor->getX(), actor->getY() - 1);
}
