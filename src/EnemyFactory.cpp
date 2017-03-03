#include "EnemyFactory.hpp"
#include "BehaviourMonster.hpp"

Actor* EnemyFactory::createRandomEnemy() {
	Actor* a = new Actor();
	a->setBehaviour(new BehaviourMonster());
	// @TODO FIX, same as for the hero in rRpg.cpp
	a->setTilesetRowIndex(2);
	return a;
}
