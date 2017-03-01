#ifndef __BEHAVIOUR_PLAYER__
#define __BEHAVIOUR_PLAYER__

#include "Behaviour.hpp"

class BehaviourPlayer : public Behaviour {
	public:
	void update(Map *map, Actor *actor);
};

#endif
