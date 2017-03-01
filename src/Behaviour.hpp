#ifndef __BEHAVIOUR__
#define __BEHAVIOUR__

class Map;
class Actor;

class Behaviour {
	public:
	virtual void update(Map *map, Actor *actor) = 0;
};

#endif
