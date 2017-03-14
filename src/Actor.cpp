#include "Actor.hpp"
#include "rRpg.hpp"

#define LIMIT_FIELD_OF_VIEW 6

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

bool Actor::seesActor(Map &map, Actor *actor) {
	int x0, y0, x1, y1, x, y,
		deltaX, deltaY, absDeltaX, absDeltaY,
		directionX, directionY,
		distance;
	float slope;
	bool actor1SeesActor2 = true;
	x0 = getX();
	y0 = getY();
	x1 = actor->getX();
	y1 = actor->getY();
	deltaX = x1 - x0;
	deltaY = y1 - y0;
	absDeltaX = abs(deltaX);
	absDeltaY = abs(deltaY);

	directionX = x0 > x1 ? -1 : 1;
	directionY = y0 > y1 ? -1 : 1;
	distance = 0;

	slope = 0;
	if (deltaX != 0) {
		slope = deltaY / (float) deltaX;
	}

	// actors are vertical or on a steep slope
	if (absDeltaX < absDeltaY) {
		for (y = y0 + directionY; y != y1; y += directionY) {
			x = deltaX == 0 ? x0 : round((y - y0 + slope * x0) / slope);
			if (map.isCellObstructingView(x, y) || distance > LIMIT_FIELD_OF_VIEW) {
				actor1SeesActor2 = false;
				break;
			}
			++distance;
		}
	}
	// actors are horizonal or on a gentle slope
	else {
		for (x = x0 + directionX; x != x1; x += directionX) {
			y = round(slope * x + y0 - slope * x0);
			if (map.isCellObstructingView(x, y) || distance > LIMIT_FIELD_OF_VIEW) {
				actor1SeesActor2 = false;
				break;
			}
			++distance;
		}
	}

	return actor1SeesActor2;
}
