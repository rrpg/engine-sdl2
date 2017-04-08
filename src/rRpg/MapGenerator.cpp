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
	_initialiseAutomaton(map);
	for (int step = 0, nbSteps = 3; step < nbSteps; ++step) {
		_automatonStep(map);
	}
	map.setStartPoint(
		(float) (rand() % map.getWidth()),
		(float) (rand() % map.getHeight())
	);
}

void MapGenerator::_initialiseAutomaton(Map &map) {
	unsigned int mapWidth = map.getWidth(),
		mapHeight = map.getHeight();
	for (unsigned int j = 0; j < mapHeight; ++j) {
		for (unsigned int i = 0; i < mapWidth; ++i) {
			E_TerrainType type;
			if (j == 0 || i == 0 || j == mapHeight - 1 || i == mapWidth - 1) {
				type = TERRAIN_ROCK_NORMAL_CENTER;
			}
			else if ((rand() % 100) > 70) {
				type = TERRAIN_ROCK_NORMAL_CENTER;
			}
			else {
				type = TERRAIN_SOIL_NORMAL_CENTER;
			}
			map.setTile(i, j, type);
		}
	}
}

void MapGenerator::_automatonStep(Map &map) {
	unsigned int mapWidth = map.getWidth(),
		mapHeight = map.getHeight(),
		deathLimit = 2,
		birthLimit = 3;
	std::vector<E_TerrainType> tmpGrid(mapWidth * mapHeight);
	E_TerrainType aliveType = TERRAIN_ROCK_NORMAL_CENTER;
	E_TerrainType deadType = TERRAIN_SOIL_NORMAL_CENTER;
	// the edges will always be of rock
	for (unsigned int j = 0; j < mapHeight; ++j) {
		for (unsigned int i = 0; i < mapWidth; ++i) {
			if (j == 0 || i == 0 || j == mapHeight - 1 || i == mapWidth - 1) {
				tmpGrid[j * mapWidth + i] = TERRAIN_ROCK_NORMAL_CENTER;
				continue;
			}
			unsigned int nbAlives = _getCountAliveNeighbours(map, i, j, aliveType);
			if (map.getTile(i, j) == aliveType) {
				if (nbAlives < deathLimit) {
					tmpGrid[j * mapWidth + i] = deadType;
				}
				else {
					tmpGrid[j * mapWidth + i] = aliveType;
				}
			}
			else {
				if (nbAlives > birthLimit) {
					tmpGrid[j * mapWidth + i] = aliveType;
				}
				else {
					tmpGrid[j * mapWidth + i] = deadType;
				}
			}
		}
	}

	map.setGrid(tmpGrid);
}

unsigned int MapGenerator::_getCountAliveNeighbours(Map &map, unsigned int i, unsigned int j, E_TerrainType aliveType) {
	return (map.getTile(i - 1, j - 1) == aliveType)
	   + (map.getTile(i, j - 1) == aliveType)
	   + (map.getTile(i + 1, j - 1) == aliveType)
	   + (map.getTile(i - 1, j) == aliveType)
	   + (map.getTile(i + 1, j) == aliveType)
	   + (map.getTile(i - 1, j + 1) == aliveType)
	   + (map.getTile(i, j + 1) == aliveType)
	   + (map.getTile(i + 1, j + 1) == aliveType);
}
