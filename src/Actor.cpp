#include "Actor.hpp"
#include "rRpg.hpp"

Actor::Actor() : m_behaviour(0) {
}

Actor::~Actor() {
	free(m_behaviour);
}

void Actor::setX(int x) { m_iX = x; }
void Actor::setY(int y) { m_iY = y; }
int Actor::getX() { return m_iX; }
int Actor::getY() { return m_iY; }
bool Actor::isTurn() { return m_bIsTurn; }
bool Actor::playedTurn() { return m_bPlayedTurn; }

int Actor::getFrame() { return m_iFrame; }
void Actor::setFrame(int frame) { m_iFrame = frame; }
int Actor::getTilesetRowIndex() { return m_iTilesetRowIndex; }
void Actor::setTilesetRowIndex(int tilesetRowIndex) { m_iTilesetRowIndex = tilesetRowIndex; }

void Actor::setBehaviour(Behaviour *b) {
	m_behaviour = b;
}

void Actor::update(rRpg *engine) {
	if (isTurn() && m_behaviour != 0 && m_behaviour->update(engine, this)) {
		_setPlayedTurn(true);
	}
}

void Actor::startTurn() {
	m_bIsTurn = true;
	_setPlayedTurn(false);
}

void Actor::_setPlayedTurn(bool played) {
	m_bPlayedTurn = played;
}

void Actor::endTurn() {
	m_bIsTurn = false;
}
