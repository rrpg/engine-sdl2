#ifndef __MOVE_LEFT_COMMAND__
#define __MOVE_LEFT_COMMAND__

#include "Move.hpp"

class MoveLeftCommand : public MoveCommand {
	public:
	bool execute(Actor* actor, Map &map);
};

#endif
