#ifndef __BEHAVIOUR_PLAYER__
#define __BEHAVIOUR_PLAYER__

#include "Behaviour.hpp"
#include <cstdint>

class BehaviourPlayer : public Behaviour {
	private:
	uint32_t m_iLastTimeActed = 0;

	public:
	bool update(rRpg *engine, Actor *actor);
};

#endif
