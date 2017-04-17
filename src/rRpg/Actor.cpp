#include "Actor.hpp"
#include "rRpg.hpp"

#define LIMIT_FIELD_OF_VIEW 6

Actor::Actor(ActorRace &race) :
	m_race(race),
	m_behaviour(0),
	m_graphic(0)
{
}

Actor::Actor(const Actor &r) :
	m_race(r.m_race),
	m_iX(r.m_iX),
	m_iY(r.m_iY),
	m_behaviour(r.m_behaviour),
	m_graphic(r.m_graphic)
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
	m_graphic = r.m_graphic;
	return *this;
}

Actor::~Actor() {
}

void Actor::setHealth(int health) { m_iHealth = health; }
void Actor::setMaxHealth(unsigned int maxHealth) { m_iMaxHealth = maxHealth; }
void Actor::setDefence(unsigned int defence) { m_iDefence = defence; }
void Actor::setAttack(unsigned int attack) { m_iAttack = attack; }
int Actor::getHealth() { return m_iHealth; }
unsigned int Actor::getMaxHealth() { return m_iMaxHealth; }
unsigned int Actor::getDefence() { return m_iDefence; }
unsigned int Actor::getAttack() { return m_iAttack; }

bool Actor::isDead() {
	return m_iHealth == 0;
}

void Actor::setX(int x) { m_iX = x; }
void Actor::setY(int y) { m_iY = y; }
int Actor::getX() { return m_iX; }
int Actor::getY() { return m_iY; }
ActorRace &Actor::getRace() { return m_race; }

void Actor::setBehaviour(Behaviour *b) {
	m_behaviour = b;
}

void Actor::setGraphic(GraphicActor *g) {
	m_graphic = g;
}

void Actor::update(rRpg *engine) {
	if (!engine->isBlocked() && m_behaviour != 0) {
		m_behaviour->update(engine, this);
	}
}

void Actor::render(unsigned int displayShiftX, unsigned int displayShiftY) {
	if (m_graphic != 0) {
		m_graphic->render(displayShiftX, displayShiftY, this);
	}
}

bool Actor::isNextTo(Actor *actor) {
	unsigned int diffX = abs(getX() - actor->getX()),
		diffY = abs(getY() - actor->getY());
	return (diffX == 1 && !diffY) || (!diffX && diffY == 1);
}

bool Actor::seesActor(Map &map, Actor *actor) {
	int x0, y0, x1, y1, x, y,
		deltaX, deltaY, absDeltaX, absDeltaY,
		directionX, directionY,
		distance;
	double slope;
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
		slope = (float) deltaY / (float) deltaX;
	}

	// actors are vertical or on a steep slope
	if (absDeltaX < absDeltaY) {
		double positionOnY0 = y0 + slope * x0;
		for (y = y0 + directionY; y != y1; y += directionY) {
			x = deltaX == 0 ? x0 : (int) round((y - positionOnY0) / slope);
			if (map.isCellObstructingView(x, y) || distance > LIMIT_FIELD_OF_VIEW) {
				actor1SeesActor2 = false;
				break;
			}
			++distance;
		}
	}
	// actors are horizonal or on a gentle slope
	else {
		double positionOnY0 = y0 - slope * x0;
		for (x = x0 + directionX; x != x1; x += directionX) {
			y = (int) round(slope * x + positionOnY0);
			if (map.isCellObstructingView(x, y) || distance > LIMIT_FIELD_OF_VIEW) {
				actor1SeesActor2 = false;
				break;
			}
			++distance;
		}
	}

	return actor1SeesActor2;
}

void Actor::attack(Actor *target) {
	unsigned int attack = rand() % m_iAttack;
	unsigned int defence = rand() % target->m_iDefence;
	int damages = attack - defence;
	// no branching max(0, damages) :p
	target->m_iHealth -= damages & -(0 < damages);
	// if the health is < 0 cap it at 0
	target->m_iHealth = target->m_iHealth & -(0 < target->m_iHealth);
}
