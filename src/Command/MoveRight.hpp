#ifndef __MOVE_RIGHT_COMMAND__
#define __MOVE_RIGHT_COMMAND__

#include "../Command.hpp"

class MoveRightCommand : public Command {
	public:
	void execute(Actor* actor);
};

#endif
