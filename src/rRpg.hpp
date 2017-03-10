#ifndef __RRPG__
#define __RRPG__

#include "ActorFactory.hpp"
#include "Map.hpp"
#include <string>

class rRpg {
	private:
	Actor* m_hero = 0;
	ActorFactory m_actorFactory;
	Map m_map;
	bool m_bIsBlocked = false;

	public:
	rRpg();
	rRpg(const rRpg &r); // copy constructor
	rRpg & operator=(const rRpg &r); // assignment
	~rRpg();
	Map &getMap();
	bool loadMap(std::string filePath);
	bool loadTaxonomy(std::string filePath);
	bool initialiseHero();
	void update();
	void render();
	bool isBlocked();
	void block();
	void unblock();
};

#endif
