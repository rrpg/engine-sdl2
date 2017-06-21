#ifndef __MAP_MANAGER__
#define __MAP_MANAGER__

#include "Map.hpp"
#include "limits.h"

class MapManager {
	private:
	void _getMapPath(std::string mapName, char filePath[PATH_MAX]);

	public:
	bool loadMap(Map &map, std::string mapName);
	bool mapExists(std::string mapName);
	bool generateMap(Map &map, std::string mapFile, S_MapSpecs specs);
};

#endif
