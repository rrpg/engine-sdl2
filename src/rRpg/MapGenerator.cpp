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
	map.initializeGrid(TERRAIN_ROCK_NORMAL);
	_initialiseAutomaton(map);
	for (int step = 0, nbSteps = 3; step < nbSteps; ++step) {
		_automatonStep(map);
	}

	_dispatchEnemies(map, 15);
	_setStartPoint(map);
}

void MapGenerator::_initialiseAutomaton(Map &map) {
	unsigned int mapWidth = map.getWidth(),
		mapHeight = map.getHeight();
	for (unsigned int j = 0; j < mapHeight; ++j) {
		for (unsigned int i = 0; i < mapWidth; ++i) {
			E_TerrainType type;
			if (j == 0 || i == 0 || j == mapHeight - 1 || i == mapWidth - 1) {
				type = TERRAIN_ROCK_NORMAL;
			}
			else if ((rand() % 100) > 70) {
				type = TERRAIN_ROCK_NORMAL;
			}
			else {
				type = TERRAIN_SOIL_NORMAL;
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
	E_TerrainType aliveType = TERRAIN_ROCK_NORMAL;
	E_TerrainType deadType = TERRAIN_SOIL_NORMAL;
	// the edges will always be of rock
	for (unsigned int j = 0; j < mapHeight; ++j) {
		for (unsigned int i = 0; i < mapWidth; ++i) {
			if (j == 0 || i == 0 || j == mapHeight - 1 || i == mapWidth - 1) {
				tmpGrid[j * mapWidth + i] = TERRAIN_ROCK_NORMAL;
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

void MapGenerator::_setStartPoint(Map &map) {
	int x = (rand() % map.getWidth()),
		y = (rand() % map.getHeight());
	if (map.isCellWalkable(x, y)) {
		map.setStartPoint((float) x, (float) y);
	}
	else {
		std::vector<bool> visited(map.getWidth() * map.getHeight(), false);
		int xOut = 0, yOut = 0;
		_findClosestWalkableCell(map, x, y, visited, xOut, yOut);
		map.setStartPoint((float) xOut, (float) yOut);
	}
}

bool MapGenerator::_findClosestWalkableCell(
	Map &map, const int x, const int y, std::vector<bool> &visited, int &xOut, int &yOut
) {
	int cellIndex = y * map.getWidth() + x;
	if (y < 0 || x < 0 || (unsigned) y >= map.getHeight() || (unsigned) x >= map.getWidth()
		|| visited[cellIndex]
	) {
		return false;
	}

	visited[cellIndex] = true;
	int neighbours[][2] = {
		{-1, 0},
		{1, 0},
		{0, -1},
		{0, 1}
	};

	for (int n = 0; n < 4; ++n) {
		if (map.isCellWalkable(x + neighbours[n][0], y + neighbours[n][1])) {
			xOut = x + neighbours[n][0];
			yOut = y + neighbours[n][1];
			return true;
		}
	}

	for (int n = 0; n < 4; ++n) {
		bool found = _findClosestWalkableCell(
			map,
			x + neighbours[n][0],
			y + neighbours[n][1],
			visited,
			xOut,
			yOut
		);

		if (found) {
			return true;
		}
	}

	return false;
}

void MapGenerator::_dispatchEnemies(Map &map, const unsigned int nbMaxEnemies) {
	for (unsigned int i = 0; i < nbMaxEnemies; ++i) {
		int x = (rand() % map.getWidth()),
			y = (rand() % map.getHeight());

		if (!map.isCellWalkable(x, y)) {
			std::vector<bool> visited(map.getWidth() * map.getHeight(), false);
			_findClosestWalkableCell(map, x, y, visited, x, y);
		}
		map.addEnemySpawnableCell((char) x, (char) y);
	}
}
