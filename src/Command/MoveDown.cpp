#include "MoveDown.hpp"

bool MoveDownCommand::execute(Actor *actor, Map &map) {
	return MoveCommand::execute(actor, map, actor->getX(), actor->getY() + 1);
}
