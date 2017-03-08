#ifndef __ACTOR_RACE__
#define __ACTOR_RACE__

#include "Actor.hpp"

class ActorRace {
	private:
	unsigned int m_iLevel1HP;

	public:
	ActorRace(unsigned int level1HP);
	Actor* createActor();
};

#endif
