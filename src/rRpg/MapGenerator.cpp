#include "MapGenerator.hpp"
#include "CaveRoom.hpp"
#include "Terrain.hpp"
#include <limits.h>
#include <algorithm>

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

	_joinRooms(map);

	_dispatchEnemies(map, 15);
	_setStartPoint(map);
}

void MapGenerator::_initialiseAutomaton(Map &map) {
	int mapWidth = map.getWidth(),
		mapHeight = map.getHeight();
	for (int j = 0; j < mapHeight; ++j) {
		for (int i = 0; i < mapWidth; ++i) {
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
	int mapWidth = map.getWidth(),
		mapHeight = map.getHeight(),
		deathLimit = 2,
		birthLimit = 3;
	size_t mapSize = (size_t) (mapWidth * mapHeight);
	std::vector<E_TerrainType> tmpGrid(mapSize);
	E_TerrainType aliveType = TERRAIN_ROCK_NORMAL;
	E_TerrainType deadType = TERRAIN_SOIL_NORMAL;
	// the edges will always be of rock
	for (int j = 0; j < mapHeight; ++j) {
		for (int i = 0; i < mapWidth; ++i) {
			size_t index = map.getTileIndex(i, j);
			if (j == 0 || i == 0 || j == mapHeight - 1 || i == mapWidth - 1) {
				tmpGrid[index] = TERRAIN_ROCK_NORMAL;
				continue;
			}
			int nbAlives = _getCountAliveNeighbours(map, i, j, aliveType);
			if (map.getTile(i, j) == aliveType) {
				if (nbAlives < deathLimit) {
					tmpGrid[index] = deadType;
				}
				else {
					tmpGrid[index] = aliveType;
				}
			}
			else {
				if (nbAlives > birthLimit) {
					tmpGrid[index] = aliveType;
				}
				else {
					tmpGrid[index] = deadType;
				}
			}
		}
	}

	map.setGrid(tmpGrid);
}

std::vector<CaveRoom::S_Room>::iterator MapGenerator::_largestRoom(std::vector<CaveRoom::S_Room> &rooms) {
	return std::max_element(
		std::begin(rooms),
		std::end(rooms),
		[] (const CaveRoom::S_Room & p1, const CaveRoom::S_Room & p2) {
			return p1.cells.size() < p2.cells.size();
		}
	);
}

void MapGenerator::_joinRooms(Map &map) {
	bool enoughRoom = false;
	do {
		CaveRoom::S_RoomCollection roomCollection = CaveRoom::findRooms(map);
		auto largest = _largestRoom(roomCollection.rooms);
		CaveRoom::S_Room largestRoom = *largest;

		if ((double) largestRoom.cells.size() / (map.getWidth() * map.getHeight()) >= 0.4200) {
			enoughRoom = true;
		}
		else {
			roomCollection.rooms.erase(largest);
			CaveRoom::S_Room secondLargestRoom = *_largestRoom(roomCollection.rooms);
			// @TODO merge largestRoom and secondLargestRoom
		}
	} while (false /*!enoughRoom*/);
}

int MapGenerator::_getCountAliveNeighbours(Map &map, int i, int j, E_TerrainType aliveType) {
	int nbAlive = (map.getTile(i - 1, j - 1) == aliveType)
	   + (map.getTile(i, j - 1) == aliveType)
	   + (map.getTile(i + 1, j - 1) == aliveType)
	   + (map.getTile(i - 1, j) == aliveType)
	   + (map.getTile(i + 1, j) == aliveType)
	   + (map.getTile(i - 1, j + 1) == aliveType)
	   + (map.getTile(i, j + 1) == aliveType)
	   + (map.getTile(i + 1, j + 1) == aliveType);

	return nbAlive;
}

void MapGenerator::_setStartPoint(Map &map) {
	int x = (rand() % map.getWidth()),
		y = (rand() % map.getHeight());
	if (!map.isCellWalkable(x, y)) {
		std::vector<bool> visited((size_t) (map.getWidth() * map.getHeight()), false);
		_findClosestWalkableCell(map, x, y, visited, x, y);
	}
	map.setStartPoint((float) x, (float) y);
}

std::vector<t_coordinates> MapGenerator::_findWalkableNeighbours(Map &map, const int x, const int y) {
	int neighbourDirections[][2] = {
		{-1, 0},
		{1, 0},
		{0, -1},
		{0, 1}
	};

	std::vector<t_coordinates> neighbours = {};
	for (int n = 0; n < 4; ++n) {
		int xN = x + neighbourDirections[n][0],
			yN = y + neighbourDirections[n][1];
		if (map.isCellWalkable(xN, yN)) {
			neighbours.push_back(std::make_pair(xN, yN));
		}
	}

	return neighbours;
}

bool MapGenerator::_findClosestWalkableCell(
	Map &map,
	const int x,
	const int y,
	std::vector<bool> &visited,
	int &xOut,
	int &yOut
) {
	size_t cellIndex = map.getTileIndex(x, y);
	if (y > map.getHeight() - 1 || x > map.getWidth() - 1 || visited[cellIndex]) {
		return false;
	}

	visited[cellIndex] = true;
	std::vector<t_coordinates> neighbours = _findWalkableNeighbours(map, x, y);
	if (neighbours.size()) {
		xOut = neighbours[0].first;
		yOut = neighbours[0].second;
		return true;
	}

	return _findClosestWalkableCell(map, x + 1, y, visited, xOut, yOut)
		|| _findClosestWalkableCell(map, x - 1, y, visited, xOut, yOut)
		|| _findClosestWalkableCell(map, x, y + 1, visited, xOut, yOut)
		|| _findClosestWalkableCell(map, x, y - 1, visited, xOut, yOut);
}

void MapGenerator::_dispatchEnemies(Map &map, const int nbMaxEnemies) {
	for (int i = 0; i < nbMaxEnemies; ++i) {
		int x = rand() % map.getWidth(),
			y = rand() % map.getHeight();

		if (!map.isCellWalkable(x, y)) {
			std::vector<bool> visited((size_t) (map.getWidth() * map.getHeight()), false);
			_findClosestWalkableCell(map, x, y, visited, x, y);
		}
		map.addEnemySpawnableCell((char) x, (char) y);
	}
}
