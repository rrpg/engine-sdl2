#include "BehaviourMonster.hpp"
#include "Command/MoveDown.hpp"
#include "rRpg.hpp"
#include <iostream>
#include <math.h>

#define LIMIT_MONSTER_FIELD_OF_VIEW 6

bool BehaviourMonster::update(rRpg *engine, Actor *actor) {
	bool updated = true;
	if (_sees(engine->getMap(), actor, engine->getHero())) {
		std::cout << actor << " sees player\n";
	}
	return updated;
}

bool BehaviourMonster::_sees(Map &map, Actor *actor1, Actor *actor2) {
	int x0, y0, x1, y1, deltaX, deltaY, absDeltaX, absDeltaY, directionX, directionY;
	x0 = actor1->getX();
	y0 = actor1->getY();
	x1 = actor2->getX();
	y1 = actor2->getY();
	deltaX = x1 - x0;
	deltaY = y1 - y0;
	absDeltaX = abs(deltaX);
	absDeltaY = abs(deltaY);

	directionX = x0 > x1 ? -1 : 1;
	directionY = y0 > y1 ? -1 : 1;

	// actors are verticals
	if (deltaX == 0) {
		for (int y = y0 + directionY; y != y1; y += directionY) {
			if (map.isCellObstructingView(x0, y)) {
				return false;
			}
		}
	}
	else if (deltaY == 0) {
		for (int x = x0 + directionX; x != x1; x += directionX) {
			if (map.isCellObstructingView(x, y0)) {
				return false;
			}
		}
	}
	// diagonale
	else if (absDeltaX == absDeltaY) {
		int x = x0 + directionX;
		for (int y = y0 + directionY; x != x1; x += directionX, y += directionY) {
			if (map.isCellObstructingView(x, y)) {
				return false;
			}
		}
	}
	// steep slope
	else if (absDeltaX < absDeltaY) {
		return false;
	}
	// gentle slope
	else if (absDeltaX > absDeltaY) {
		return false;
	}

	return true;
}
