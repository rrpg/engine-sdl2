#ifndef __COMMAND__
#define __COMMAND__

class Actor;
class Map;

class Command {
	public:
	virtual ~Command() {};
	virtual bool execute(Actor *actor, Map &map, int xDest, int yDest) = 0;
};

#endif
