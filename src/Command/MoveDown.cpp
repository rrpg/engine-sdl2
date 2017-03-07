#include "MoveDown.hpp"

bool MoveDownCommand::execute(Actor *actor, Map &map) {
	return _execute(actor, map, actor->getX(), actor->getY() + 1);
}
