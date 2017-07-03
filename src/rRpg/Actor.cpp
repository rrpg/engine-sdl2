#include "Actor.hpp"
#include "rRpg.hpp"
#include "Behaviour/Behaviour.hpp"
#include "GUI/Actor.hpp"
#include <limits.h>
#include <SDL2/SDL.h>

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
void Actor::setMaxHealth(int maxHealth) { m_iMaxHealth = maxHealth; }
void Actor::setDefence(int defence) { m_iDefence = defence; }
void Actor::setAttack(int attackValue) { m_iAttack = attackValue; }
int Actor::getHealth() { return m_iHealth; }
int Actor::getMaxHealth() { return m_iMaxHealth; }
int Actor::getDefence() { return m_iDefence; }
int Actor::getAttack() { return m_iAttack; }

bool Actor::isDead() {
	return m_iHealth == 0;
}

void Actor::setX(int x) {
	if (x > m_iX) {
		m_eOrientation = RIGHT;
	}
	else if (x < m_iX) {
		m_eOrientation = LEFT;
	}
	m_iX = x;

}
void Actor::setY(int y) { m_iY = y; }
int Actor::getX() { return m_iX; }
int Actor::getY() { return m_iY; }
E_ActorOrientation Actor::getOrientation() { return m_eOrientation; }
ActorRace &Actor::getRace() { return m_race; }

void Actor::setBehaviour(Behaviour *b) {
	m_behaviour = b;
}

void Actor::setGraphic(GraphicActor *g) {
	m_graphic = g;
}

void Actor::setLastTimeHit() {
	m_iLastTimeHit = SDL_GetTicks();
}

uint32_t Actor::getLastTimeHit() {
	return m_iLastTimeHit;
}

void Actor::update(rRpg *engine) {
	if (!engine->isBlocked() && m_behaviour != 0) {
		m_behaviour->update(engine, this);
	}
}

void Actor::render(int displayShiftX, int displayShiftY) {
	if (m_graphic != 0) {
		m_graphic->render(displayShiftX, displayShiftY, this);
	}
}

bool Actor::isNextTo(std::shared_ptr<Actor> actor) {
	int x0 = getX(),
		x1 = actor->getX(),
		y0 = getY(),
		y1 = actor->getY();
	bool isNext = (x0 + 1 == x1) || (x1 + 1 == x0);
	bool isAbove = (y0 + 1 == y1) || (y1 + 1 == y0);
	return (isNext && y0 == y1) || (x0 == x1 && isAbove);
}

bool Actor::seesActor(Map &map, std::shared_ptr<Actor> actor) {
	int x0 = getX(),
		y0 = getY(),
		x1 = actor->getX(),
		y1 = actor->getY(),
		x, y,
		directionX, directionY;
	int deltaX, deltaY, absDeltaX, absDeltaY;
	double slope,
		positionOnY0;
	bool actor1SeesActor2 = true;
	deltaX = x1 - x0;
	deltaY = y1 - y0;
	absDeltaX = abs(deltaX);
	absDeltaY = abs(deltaY);

	if (absDeltaY > LIMIT_FIELD_OF_VIEW || absDeltaX > LIMIT_FIELD_OF_VIEW) {
		return false;
	}

	directionX = (x0 < x1) - (x0 > x1);
	directionY = (y0 < y1) - (y0 > y1);

	slope = 0;
	if (x1 != x0) {
		slope = (float) deltaY / (float) deltaX;
	}

	positionOnY0 = y0 - slope * x0;
	// actors are vertical or on a steep slope
	if (absDeltaX < absDeltaY) {
		for (y = y0 + directionY; y != y1; y += directionY) {
			x = x1 == x0 ? x0 : (int) round((y - positionOnY0) / slope);
			if (map.isCellObstructingView(x, y)) {
				actor1SeesActor2 = false;
				break;
			}
		}
	}
	// actors are horizonal or on a gentle slope
	else {
		for (x = x0 + directionX; x != x1; x += directionX) {
			y = (int) round(slope * x + positionOnY0);
			if (map.isCellObstructingView(x, y)) {
				actor1SeesActor2 = false;
				break;
			}
		}
	}

	return actor1SeesActor2;
}

void Actor::attack(std::shared_ptr<Actor> target) {
	int attackValue = rand() % m_iAttack;
	int defence = rand() % target->m_iDefence;
	int damages = attackValue - defence;
	// no branching max(0, damages) :p
	target->m_iHealth -= damages & -(0 < damages);
	// if the health is < 0 cap it at 0
	target->m_iHealth = target->m_iHealth & -(0 < target->m_iHealth);
	target->setLastTimeHit();
}
