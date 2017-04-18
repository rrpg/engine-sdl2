#include "ActorRace.hpp"

ActorRace::ActorRace(unsigned int level1HP, unsigned int level1Defence, unsigned int level1Attack) :
	m_iLevel1HP(level1HP),
	m_iLevel1Defence(level1Defence),
	m_iLevel1Attack(level1Attack)
{
}

Actor* ActorRace::createActor() {
	Actor* actor = new Actor(*this);
	actor->setHealth((int) m_iLevel1HP);
	actor->setMaxHealth(m_iLevel1HP);
	actor->setDefence(m_iLevel1Defence);
	actor->setAttack(m_iLevel1Attack);
	return actor;
}

void ActorRace::addTilesetName(std::string name) {
	m_vTilesetNames.push_back(name);
}

void ActorRace::setSpriteX(unsigned int spriteX) {
	m_iSpriteX = spriteX;
}

void ActorRace::setSpriteY(unsigned int spriteY) {
	m_iSpriteY = spriteY;
}

std::string ActorRace::getTilesetName() {
	return m_vTilesetNames[0];
}

unsigned int ActorRace::getSpriteX() {
	return m_iSpriteX;
}

unsigned int ActorRace::getSpriteY() {
	return m_iSpriteY;
}
