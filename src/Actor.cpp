#include "Actor.hpp"
#include "rRpg.hpp"

Actor::Actor(ActorRace &race) : m_race(race), m_behaviour(0) {
}

Actor::Actor(const Actor &r) :
	m_race(r.m_race),
	m_iX(r.m_iX),
	m_iY(r.m_iY),
	m_behaviour(r.m_behaviour)
{
}

Actor & Actor::operator=(const Actor &r) {
	// check for "self assignment" and do nothing in that case
	if (this == &r) {
		return *this;
	}

	m_iX = r.m_iX;
	m_iY = r.m_iY;
	m_behaviour = r.m_behaviour;
	return *this;
}

Actor::~Actor() {
	//@TODO store the bhaviours in a manager and provide them as reference
	delete m_behaviour;
}

void Actor::setHealth(int health) { m_iHealth = health; }
void Actor::setMaxHealth(unsigned int maxHealth) { m_iMaxHealth = maxHealth; }
int Actor::getHealth() { return m_iHealth; }
unsigned int Actor::getMaxHealth() { return m_iMaxHealth; }

void Actor::setX(int x) { m_iX = x; }
void Actor::setY(int y) { m_iY = y; }
int Actor::getX() { return m_iX; }
int Actor::getY() { return m_iY; }
ActorRace &Actor::getRace() { return m_race; }

void Actor::setBehaviour(Behaviour *b) {
	m_behaviour = b;
}

void Actor::update(rRpg *engine) {
	if (!engine->isBlocked() && m_behaviour != 0) {
		m_behaviour->update(engine, this);
	}
}
