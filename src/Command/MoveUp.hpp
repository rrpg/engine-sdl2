#ifndef __MOVE_UP_COMMAND__
#define __MOVE_UP_COMMAND__

#include "../Command.hpp"

class MoveUpCommand : public Command {
	public:
	void execute(Actor* actor);
};

#endif
