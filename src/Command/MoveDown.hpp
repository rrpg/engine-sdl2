#ifndef __MOVE_DOWN_COMMAND__
#define __MOVE_DOWN_COMMAND__

#include "../Command.hpp"

class MoveDownCommand : public Command {
	public:
	void execute(Actor* actor);
};

#endif
