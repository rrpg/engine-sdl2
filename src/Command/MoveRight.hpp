#ifndef __MOVE_RIGHT_COMMAND__
#define __MOVE_RIGHT_COMMAND__

#include "Move.hpp"

class MoveRightCommand : public MoveCommand {
	public:
	bool execute(Actor* actor, Map *map);
};

#endif
