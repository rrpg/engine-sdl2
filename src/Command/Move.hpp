#ifndef __MOVE_COMMAND__
#define __MOVE_COMMAND__

#include "../Command.hpp"

class MoveCommand : public Command {
	public:
	bool execute(Actor* actor, Map &map, int xDest, int yDest);
	virtual bool execute(Actor* actor, Map &map) = 0;
};

#endif
