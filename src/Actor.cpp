#include "Actor.hpp"

const uint32_t timeBetweenActions = 100;

Actor::Actor() : m_behaviour(0) {
}

Actor::~Actor() {
	free(m_behaviour);
}

void Actor::setX(int x) { m_iX = x; }
void Actor::setY(int y) { m_iY = y; }
int Actor::getX() { return m_iX; }
int Actor::getY() { return m_iY; }

int Actor::getFrame() { return m_iFrame; }
void Actor::setFrame(int frame) { m_iFrame = frame; }
int Actor::getTilesetRowIndex() { return m_iTilesetRowIndex; }
void Actor::setTilesetRowIndex(int tilesetRowIndex) { m_iTilesetRowIndex = tilesetRowIndex; }

void Actor::setBehaviour(Behaviour *b) {
	m_behaviour = b;
}

void Actor::update(Map *map) {
	uint32_t currentTimestamp = SDL_GetTicks();
	if (m_behaviour != 0
		&& currentTimestamp - m_iLastTimeActed > timeBetweenActions
	) {
		m_behaviour->update(map, this);
		m_iLastTimeActed = currentTimestamp;
	}
}
