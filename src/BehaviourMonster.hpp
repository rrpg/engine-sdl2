#ifndef __BEHAVIOUR_MONSTER__
#define __BEHAVIOUR_MONSTER__

#include "Behaviour.hpp"
#include "Map.hpp"

class BehaviourMonster : public Behaviour {
	private:
	bool _sees(Map &map, Actor *actor1, Actor *actor2);

	public:
	bool update(rRpg *engine, Actor *actor);
};

#endif
