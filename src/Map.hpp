#ifndef __MAP__
#define __MAP__

#include "Actor.hpp"
#include <stdint.h>
#include <vector>

class Map {
	private:
	uint8_t m_aGrid[2500];
	std::vector<Actor*> m_vActors = {};

	public:
	void addActor(Actor *actor);
};

#endif
