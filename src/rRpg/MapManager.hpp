#ifndef __MAP_MANAGER__
#define __MAP_MANAGER__

#include "Map.hpp"

class MapManager {
	public:
	bool loadMap(Map &map, std::string mapName, int level);
};

#endif
