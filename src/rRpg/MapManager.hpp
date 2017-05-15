#ifndef __MAP_MANAGER__
#define __MAP_MANAGER__

#include "Map.hpp"

class MapManager {
	private:
	Map m_map;

	public:
	MapManager();
	bool loadMap(std::string mapName, int level);
	Map &getMap();
};

#endif
