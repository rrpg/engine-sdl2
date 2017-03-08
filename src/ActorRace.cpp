#include "ActorRace.hpp"

ActorRace::ActorRace(unsigned int level1HP) : m_iLevel1HP(level1HP) {
}

Actor* ActorRace::createActor() {
	Actor* actor = new Actor(*this);
	actor->setHealth((int) m_iLevel1HP);
	actor->setMaxHealth(m_iLevel1HP);
	return actor;
}

void ActorRace::setTilesetName(std::string name) {
	m_sTilesetName = name;
}

void ActorRace::setSpriteX(unsigned int spriteX) {
	m_iSpriteX = spriteX;
}

void ActorRace::setSpriteY(unsigned int spriteY) {
	m_iSpriteY = spriteY;
}
