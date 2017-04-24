#ifndef __BEHAVIOUR_PLAYER__
#define __BEHAVIOUR_PLAYER__

#include "../Behaviour.hpp"
#include "../Map.hpp"
#include <cstdint>

class BehaviourPlayer : public Behaviour {
	private:
	uint32_t m_iLastTimeActed = 0;
	bool _isDirectionPressed(unsigned int &x, unsigned int &y);
	bool _tryMove(Actor *actor, Map &map, unsigned int x, unsigned int y);
	bool _tryAttack(Actor *actor, Map &map, unsigned int x, unsigned int y);

	public:
	bool update(rRpg *engine, Actor *actor);
};

#endif
