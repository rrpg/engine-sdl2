#ifndef __MOVE_COMMAND__
#define __MOVE_COMMAND__

#include "../Command.hpp"

class MoveCommand : public Command {
	public:
	bool execute(Actor* actor, Map &map, unsigned int xDest, unsigned int yDest);
};

#endif
