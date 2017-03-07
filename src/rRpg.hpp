#ifndef __RRPG__
#define __RRPG__

#include "Actor.hpp"
#include "Map.hpp"
#include <string>

class rRpg {
	private:
	Actor* m_hero = 0;
	Map m_map;

	public:
	rRpg();
	rRpg(const rRpg &r); // copy constructor
	rRpg & operator=(const rRpg &r); // assignment
	~rRpg();
	Map &getMap();
	void loadMap(std::string filePath);
	void initialiseHero();
	void update();
	void render();
};

#endif
