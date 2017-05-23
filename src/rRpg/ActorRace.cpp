#include "ActorRace.hpp"

ActorRace::ActorRace(int level1HP, int level1Defence, int level1Attack) :
	m_data(S_ActorRaceData())
{
	m_data.level1HP = level1HP;
	m_data.level1Defence = level1Defence;
	m_data.level1Attack = level1Attack;
}

Actor* ActorRace::createActor() {
	Actor* actor = new Actor(*this);
	actor->setHealth((int) m_data.level1HP);
	actor->setMaxHealth(m_data.level1HP);
	actor->setDefence(m_data.level1Defence);
	actor->setAttack(m_data.level1Attack);
	return actor;
}

void ActorRace::addTilesetName(std::string name) {
	m_data.tilesetNames.push_back(name);
}

void ActorRace::setTimePerFrame(int timePerFrame) {
	m_data.timePerFrame = timePerFrame;
}

void ActorRace::setSpriteX(int spriteX) {
	m_data.spriteX = spriteX;
}

void ActorRace::setSpriteY(int spriteY) {
	m_data.spriteY = spriteY;
}

std::string ActorRace::getTilesetName() {
	int tilesetIndex = 0;
	if (m_data.timePerFrame) {
		uint32_t currTime = SDL_GetTicks();
		int durationAnimationCycle = m_data.timePerFrame * (int) m_data.tilesetNames.size();
		int timeInCycle = (int) currTime % durationAnimationCycle;
		tilesetIndex = timeInCycle / m_data.timePerFrame;
	}
	return m_data.tilesetNames[(size_t) tilesetIndex];
}

int ActorRace::getSpriteX() {
	return m_data.spriteX;
}

int ActorRace::getSpriteY() {
	return m_data.spriteY;
}
