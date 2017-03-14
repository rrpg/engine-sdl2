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
	int x0, y0, x1, y1, x, y,
		deltaX, deltaY, absDeltaX, absDeltaY,
		directionX, directionY;
	float slope;
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

	slope = 0;
	if (deltaX != 0) {
		slope = deltaY / (float) deltaX;
	}

	// actors are vertical or on a steep slope
	if (absDeltaX < absDeltaY) {
		for (y = y0 + directionY; y != y1; y += directionY) {
			x = deltaX == 0 ? x0 : round((y - y0 + slope * x0) / slope);
			if (map.isCellObstructingView(x, y)) {
				return false;
			}
		}
	}
	// actors are horizonal or on a gentle slope
	else {
		for (x = x0 + directionX; x != x1; x += directionX) {
			y = round(slope * x + y0 - slope * x0);
			if (map.isCellObstructingView(x, y)) {
				return false;
			}
		}
	}

	return true;
}
