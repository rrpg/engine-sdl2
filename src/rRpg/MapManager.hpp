#ifndef __MAP_MANAGER__
#define __MAP_MANAGER__

#include "Map.hpp"
#include "limits.h"

class MapManager {
	private:
	void _getMapPath(std::string mapName, int level, char filePath[PATH_MAX]);

	public:
	bool loadMap(Map &map, std::string mapName, int level);
	bool mapExists(std::string mapName, int level);
	bool generateMap(Map &map, std::string mapName, int level);
};

#endif
