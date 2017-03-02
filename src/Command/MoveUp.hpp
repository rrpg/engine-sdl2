#ifndef __MOVE_UP_COMMAND__
#define __MOVE_UP_COMMAND__

#include "Move.hpp"

class MoveUpCommand : public MoveCommand {
	public:
	bool execute(Actor* actor, Map* map);
};

#endif
