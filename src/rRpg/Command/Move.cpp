#include "Move.hpp"
#include "Map.hpp"
#include "Actor.hpp"

bool MoveCommand::execute(Actor* actor, Map &map, int xDest, int yDest) {
	return map.moveActor(actor, xDest, yDest);
}
