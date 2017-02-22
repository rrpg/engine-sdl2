#ifndef __MAP__
#define __MAP__

#include "Actor.hpp"
#include <stdint.h>
#include <vector>

class Map {
	private:
	unsigned int m_iWidth = 0;
	unsigned int m_iHeight = 0;
	uint8_t *m_aGrid = 0;
	std::vector<Actor*> m_vActors = {};

	public:
	void addActor(Actor *actor);
	void clean();
};

#endif
