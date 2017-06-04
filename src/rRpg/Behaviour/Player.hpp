#ifndef __BEHAVIOUR_PLAYER__
#define __BEHAVIOUR_PLAYER__

#include "Behaviour/Behaviour.hpp"
#include <cstdint>

class Map;
class rRpg;
class Actor;

class BehaviourPlayer : public Behaviour {
	private:
	uint32_t m_iLastTimeActed = 0;
	bool _isDirectionPressed(int &x, int &y);
	bool _tryMove(Actor *actor, rRpg *engine, int x, int y);
	bool _tryAttack(Actor *actor, Map &map, int x, int y);

	public:
	bool update(rRpg *engine, Actor *actor);
};

#endif
