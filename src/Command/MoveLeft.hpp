#ifndef __MOVE_LEFT_COMMAND__
#define __MOVE_LEFT_COMMAND__

#include "../Command.hpp"

class MoveLeftCommand : public Command {
	public:
	void execute(Actor* actor);
};

#endif
