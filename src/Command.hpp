#ifndef __COMMAND__
#define __COMMAND__

#include "Actor.hpp"

class Command {
	public:
	virtual ~Command() {};
	virtual void execute(Actor *actor) = 0;
};

#endif
