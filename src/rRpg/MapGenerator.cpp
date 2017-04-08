#include "MapGenerator.hpp"
#include "Terrain.hpp"

MapGenerator::MapGenerator() {
}

Map MapGenerator::generate(E_MapType type, short width, short height) {
	Map map;
	map.setDimensions(width, height);
	map.setDisplayTileDimensions(16, 16);

	if (type == CAVE) {
		_generateCave(map);
	}

	return map;
}

void MapGenerator::_generateCave(Map &map) {
	map.initializeGrid(TERRAIN_ROCK_NORMAL_CENTER);
	unsigned int mapWidth = map.getWidth(),
		mapHeight = map.getHeight();
	bool startPointSet = 0;
	for (unsigned int j = 0; j < mapHeight; ++j) {
		for (unsigned int i = 0; i < mapWidth; ++i) {
			E_TerrainType type;
			if (rand() % 100 > 30) {
				type = TERRAIN_SOIL_NORMAL_CENTER;
				if (!startPointSet && (rand() % 100) > 90) {
					startPointSet = 1;
					map.setStartPoint((float) i, (float) j);
				}
			}
			else {
				type = TERRAIN_ROCK_NORMAL_CENTER;
			}
			map.setTile(i, j, type);
		}
	}
}
