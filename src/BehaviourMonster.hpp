#ifndef __BEHAVIOUR_MONSTER__
#define __BEHAVIOUR_MONSTER__

#include "Behaviour.hpp"

class BehaviourMonster : public Behaviour {
	public:
	bool update(Map *map, Actor *actor);
};

#endif
