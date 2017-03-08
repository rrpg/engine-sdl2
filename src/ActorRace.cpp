#include "ActorRace.hpp"

ActorRace::ActorRace(unsigned int level1HP) : m_iLevel1HP(level1HP) {
}

Actor* ActorRace::createActor() {
	Actor* actor = new Actor(*this);
	actor->setHealth((int) m_iLevel1HP);
	actor->setMaxHealth(m_iLevel1HP);
	return actor;
}
