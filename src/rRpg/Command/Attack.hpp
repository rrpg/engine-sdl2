#ifndef __ATTACK_COMMAND__
#define __ATTACK_COMMAND__

#include "../Command.hpp"

class AttackCommand : public Command {
	public:
	bool execute(Actor* actor, Map &map, int xDest, int yDest);
};

#endif
