#ifndef __COMMAND__
#define __COMMAND__

#include "Actor.hpp"
#include "Map.hpp"

class Command {
	public:
	virtual ~Command() {};
	virtual bool execute(Actor *actor, Map &map, int xDest, int yDest) = 0;
};

#endif