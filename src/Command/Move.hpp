#ifndef __MOVE_COMMAND__
#define __MOVE_COMMAND__

#include "../Command.hpp"

class MoveCommand : public Command {
	protected:
	void _execute(Actor* actor, int xDest, int yDest);
};

#endif
