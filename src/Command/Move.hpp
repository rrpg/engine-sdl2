#ifndef __MOVE_COMMAND__
#define __MOVE_COMMAND__

#include "../Command.hpp"

class MoveCommand : public Command {
	protected:
	bool _execute(Actor* actor, Map &map, int xDest, int yDest);
};

#endif
