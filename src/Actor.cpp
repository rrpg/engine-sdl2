#include "Actor.hpp"

void Actor::setX(int x) { m_iX = x; }
void Actor::setY(int y) { m_iY = y; }
int Actor::getX() { return m_iX; }
int Actor::getY() { return m_iY; }

int Actor::getFrame() { return m_iFrame; }
void Actor::setFrame(int frame) { m_iFrame = frame; }
int Actor::getTilesetRowIndex() { return m_iTilesetRowIndex; }
void Actor::setTilesetRowIndex(int tilesetRowIndex) { m_iTilesetRowIndex = tilesetRowIndex; }
