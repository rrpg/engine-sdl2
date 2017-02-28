#ifndef __COMMAND__
#define __COMMAND__

#include "Actor.hpp"
#include "Map.hpp"

class Command {
	public:
	virtual ~Command() {};
	virtual void execute(Actor *actor, Map *map) = 0;
};

#endif
