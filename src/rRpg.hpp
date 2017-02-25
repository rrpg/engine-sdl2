#ifndef __RRPG__
#define __RRPG__

#include "Actor.hpp"
#include "Map.hpp"
#include <string>

class rRpg {
	private:
	Actor m_hero;
	Map m_map;

	public:
	rRpg();
	~rRpg();
	void loadMap(std::string filePath);
	void update();
	void render();
};

#endif
