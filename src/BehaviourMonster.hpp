#ifndef __BEHAVIOUR_MONSTER__
#define __BEHAVIOUR_MONSTER__

#include "Behaviour.hpp"
#include "Map.hpp"

class BehaviourMonster : public Behaviour {
	private:

	public:
	bool update(rRpg *engine, Actor *actor);
};

#endif
