#ifndef __RRPG__
#define __RRPG__

#include "Actor.hpp"
#include "Map.hpp"

class rRpg {
	private:
	Actor m_hero;
	Map m_map;

	public:
	rRpg();
	void update();
	void render();
};

#endif
