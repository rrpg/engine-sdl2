#include "EnemyFactory.hpp"

Actor* EnemyFactory::createRandomEnemy() {
	Actor* a = new Actor();
	// @TODO FIX, same as for the hero in rRpg.cpp
	a->setTilesetRowIndex(2);
	return a;
}
