#ifndef __RRPG__
#define __RRPG__

#include <vector>
#include <stdint.h>
#include "Actor.hpp"

class rRpg {
	private:
	uint8_t m_aMap[2500];
	Actor m_hero;
	std::vector<Actor*> m_vActors;

	public:
	rRpg();
};

#endif
