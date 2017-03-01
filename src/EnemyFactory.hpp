#ifndef __ENEMY_FACTORY__
#define __ENEMY_FACTORY__

#include "Actor.hpp"

class EnemyFactory {
	public:
	Actor* createRandomEnemy();
};

#endif
