#include "ActorRace.hpp"

ActorRace::ActorRace(S_ActorRaceData data) :
	m_data(data)
{
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
