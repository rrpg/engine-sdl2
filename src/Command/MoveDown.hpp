#ifndef __MOVE_DOWN_COMMAND__
#define __MOVE_DOWN_COMMAND__

#include "Move.hpp"

class MoveDownCommand : public MoveCommand {
	public:
	bool execute(Actor* actor, Map *map);
};

#endif
