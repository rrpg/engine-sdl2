#ifndef __RRPG__
#define __RRPG__

#include "ActorFactory.hpp"
#include "MapManager.hpp"
#include <string>
#include <memory>

class rRpg {
	private:
	std::shared_ptr<Actor> m_hero;
	ActorFactory m_actorFactory;
	MapManager m_mapManager;
	bool m_bIsBlocked = false;
	std::string m_sTilesFile = "";
	std::string m_sObjectsFile = "";

	public:
	rRpg();
	~rRpg();
	Map &getMap();
	std::shared_ptr<Actor> getHero();
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
