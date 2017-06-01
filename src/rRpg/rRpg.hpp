#ifndef __RRPG__
#define __RRPG__

#include "ActorFactory.hpp"
#include "MapManager.hpp"
#include <string>

class rRpg {
	private:
	Actor* m_hero = 0;
	ActorFactory m_actorFactory;
	MapManager m_mapManager;
	bool m_bIsBlocked = false;
	std::string m_sTilesFile = "";
	std::string m_sObjectsFile = "";

	public:
	rRpg();
	rRpg(const rRpg &r); // copy constructor
	rRpg & operator=(const rRpg &r); // assignment
	~rRpg();
	Map &getMap();
	Actor *getHero();
	void setTilesFile(std::string);
	void setObjectsFile(std::string objectsFilePath);
	bool loadMap(std::string mapName, int level);
	bool loadTaxonomy(std::string filePath);
	void initialiseHero();
	void update();
	void render();
	bool isBlocked();
	void block();
	void unblock();
};

#endif
