#ifndef __BEHAVIOUR_MONSTER__
#define __BEHAVIOUR_MONSTER__

#include "../Behaviour.hpp"
#include "../Map.hpp"

class BehaviourMonster : public Behaviour {
	private:
	void _executeMove(rRpg *engine, Actor *actor, const unsigned int x, const unsigned int y);
	void _executeRandomMove(rRpg *engine, Actor *actor);

	public:
	bool update(rRpg *engine, Actor *actor);
};

#endif
