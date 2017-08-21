#include "Map/Generator.hpp"
#include "Terrain.hpp"
#include "Map.hpp"
#include <limits.h>
#include <algorithm>

#define STAIR_UP -1
#define STAIR_DOWN 1

#define CAVE_MAX_LEVEL 10

const unsigned int CURRENT_CELL_IS_WALKABLE = CURRENT_CELL;
const unsigned int CURRENT_CELL_IS_RIM = NEIGHBOUR_NORTH | NEIGHBOUR_SOUTH | NEIGHBOUR_EAST | NEIGHBOUR_WEST;

MapGenerator::MapGenerator(Map &map) : m_map(map) {
}

void MapGenerator::generate(S_MapSpecs specs) {
	m_map.setType(specs.type);
	m_map.setDimensions(specs.width, specs.height);

	if (specs.type == CAVE) {
		_generateCave(specs);
	}
}

void MapGenerator::_generateCave(S_MapSpecs specs) {
	m_map.initializeGrid(TERRAIN_ROCK_NORMAL);
	_initialiseAutomaton();
	for (int step = 0, nbSteps = 3; step < nbSteps; ++step) {
		_automatonStep();
	}

	_joinRooms();
	_cleanRooms();

	_setStartPoint();
	if (specs.hasEnemies) {
		_dispatchEnemies(specs.width * specs.height * 4 / 1000);
	}

	if (specs.level == 0) {
		_addEntrance();
	}

	if (specs.level < CAVE_MAX_LEVEL) {
		_addStair(STAIR_DOWN);
	}

	if (specs.level == CAVE_MAX_LEVEL) {
		_addCaveArtifact();
	}
}

void MapGenerator::_initialiseAutomaton() {
	int mapWidth = m_map.getWidth(),
		mapHeight = m_map.getHeight();
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
			m_map.setTile(i, j, type);
		}
	}
}

void MapGenerator::_automatonStep() {
	int mapWidth = m_map.getWidth(),
		mapHeight = m_map.getHeight(),
		deathLimit = 2,
		birthLimit = 3;
	size_t mapSize = (size_t) (mapWidth * mapHeight);
	std::vector<E_TerrainType> tmpGrid(mapSize);
	E_TerrainType aliveType = TERRAIN_ROCK_NORMAL;
	E_TerrainType deadType = TERRAIN_SOIL_NORMAL;
	// the edges will always be of rock
	for (int j = 0; j < mapHeight; ++j) {
		for (int i = 0; i < mapWidth; ++i) {
			size_t index = m_map.getTileIndex(i, j);
			if (j == 0 || i == 0 || j == mapHeight - 1 || i == mapWidth - 1) {
				tmpGrid[index] = TERRAIN_ROCK_NORMAL;
				continue;
			}
			int nbAlives = _getCountAliveNeighbours(i, j, aliveType);
			if (m_map.getTile(i, j) == aliveType) {
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

	m_map.setGrid(tmpGrid);
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

void MapGenerator::_joinRooms() {
	bool enoughRoom = false;
	do {
		CaveRoom::S_RoomCollection roomCollection = CaveRoom::findRooms(m_map);
		auto largest = _largestRoom(roomCollection.rooms);
		CaveRoom::S_Room largestRoom = *largest;

		double sizeLargestRoom = (double) largestRoom.cells.size() / (m_map.getWidth() * m_map.getHeight());
		if (sizeLargestRoom >= 0.4200 || roomCollection.rooms.size() == 1) {
			enoughRoom = true;
		}
		else {
			roomCollection.rooms.erase(largest);
			CaveRoom::S_Room secondLargestRoom = *_largestRoom(roomCollection.rooms);
			// merge largestRoom and secondLargestRoom
			_digBetweenRooms(
				roomCollection,
				largestRoom.cells[(size_t) rand() % largestRoom.cells.size()],
				secondLargestRoom.cells[(size_t) rand() % secondLargestRoom.cells.size()]
			);
		}
	} while (!enoughRoom);
}

size_t MapGenerator::_digBetweenRooms(CaveRoom::S_RoomCollection &roomCollection, size_t cell1Index, size_t cell2Index) {
	int xStart = (signed) cell1Index % m_map.getWidth(),
		yStart = (signed) cell1Index / m_map.getWidth(),
		xEnd = (signed) cell2Index % m_map.getWidth(),
		yEnd = (signed) cell2Index / m_map.getWidth(),
		xWay = (xStart < xEnd) - (xStart > xEnd),
		yWay = (yStart < yEnd) - (yStart > yEnd),
		xCurr = xStart,
		yCurr = yStart;
	size_t cellStart = m_map.getTileIndex(xStart, yStart),
		cellIndex;

	std::vector<t_coordinates> cellsToDig = {};
	while (xCurr != xEnd || yCurr != yEnd) {
		cellIndex = m_map.getTileIndex(xCurr, yCurr);
		// wall found, add it to the list of cells to dig
		if (!m_map.isCellWalkable(xCurr, yCurr)) {
			cellsToDig.push_back({xCurr, yCurr});
			// @TODO stop if one of the neighbour is a soil different than the
			// start cell
		}
		// we are back in the first room
		else if (roomCollection.cellRoomMapping[cellIndex] == roomCollection.cellRoomMapping[cellStart]) {
			cellsToDig.clear();
		}
		else {
			break;
		}

		if (xCurr != xEnd) {
			xCurr += xWay;
		}
		else {
			yCurr += yWay;
		}
	}

	for (auto cell: cellsToDig) {
		// add cell to room
		m_map.setTile(cell.first, cell.second, TERRAIN_SOIL_NORMAL);
	}

	return cellIndex;
}

void MapGenerator::_cleanRooms() {
	CaveRoom::S_RoomCollection roomCollection = CaveRoom::findRooms(m_map);
	auto largest = _largestRoom(roomCollection.rooms);
	roomCollection.rooms.erase(largest);
	for_each(
		roomCollection.rooms.begin(),
		roomCollection.rooms.end(),
		[&](const CaveRoom::S_Room &room) {
			for_each(
				room.cells.begin(),
				room.cells.end(),
				[&](const unsigned int &cellIndex) {
					m_map.setTile(
						(signed) cellIndex % m_map.getWidth(),
						(signed) cellIndex / m_map.getWidth(),
						TERRAIN_ROCK_NORMAL
					);
				}
			);
		}
	);
}

int MapGenerator::_getCountAliveNeighbours(int i, int j, E_TerrainType aliveType) {
	int nbAlive = (m_map.getTile(i - 1, j - 1) == aliveType)
	   + (m_map.getTile(i, j - 1) == aliveType)
	   + (m_map.getTile(i + 1, j - 1) == aliveType)
	   + (m_map.getTile(i - 1, j) == aliveType)
	   + (m_map.getTile(i + 1, j) == aliveType)
	   + (m_map.getTile(i - 1, j + 1) == aliveType)
	   + (m_map.getTile(i, j + 1) == aliveType)
	   + (m_map.getTile(i + 1, j + 1) == aliveType);

	return nbAlive;
}

void MapGenerator::_setStartPoint() {
	int x = (rand() % m_map.getWidth()),
		y = (rand() % m_map.getHeight());
	std::vector<bool> visited((size_t) (m_map.getWidth() * m_map.getHeight()), false);
	_findClosestCell(CURRENT_CELL_IS_WALKABLE | CURRENT_CELL_IS_RIM, x, y, visited, x, y);
	m_map.setStartPoint((float) x, (float) y);
	_addStair(STAIR_UP, x, y);
}

unsigned int MapGenerator::_findWalkableMask(const int x, const int y, std::vector<std::pair<int, int>> &neighbours) {
	int neighbourDirections[][3] = {
		{CURRENT_CELL, 0, 0},
		{NEIGHBOUR_WEST, -1, 0},
		{NEIGHBOUR_EAST, 1, 0},
		{NEIGHBOUR_NORTH, 0, -1},
		{NEIGHBOUR_SOUTH, 0, 1}
	};

	unsigned int walkableNeighbours = 0;
	for (int n = 0; n < 5; ++n) {
		int xN = x + neighbourDirections[n][1],
			yN = y + neighbourDirections[n][2];
		if (m_map.isCellWalkable(xN, yN, WALKABLE_CONSTRAINT_ACTOR_SPAWN_LOCATION)) {
			walkableNeighbours |= (unsigned) neighbourDirections[n][0];
			neighbours.push_back(std::make_pair(xN, yN));
		}
	}

	return walkableNeighbours;
}

// constraint is a bit mask where the bit to 1 are those of the walkable
// neighbours (and/or current cell if the current cell is walkable)
bool MapGenerator::_findClosestCell(
	unsigned int constraint,
	const int x,
	const int y,
	std::vector<bool> &visited,
	int &xOut,
	int &yOut
) {
	size_t cellIndex = m_map.getTileIndex(x, y);
	if (!m_map.areCoordinatesValid(x, y) || visited[cellIndex]) {
		return false;
	}

	std::vector<std::pair<int, int>> neighbours;
	unsigned int mask = _findWalkableMask(x, y, neighbours);
	if (mask & constraint) {
		xOut = neighbours[0].first;
		yOut = neighbours[0].second;

		return true;
	}

	visited[cellIndex] = true;

	return _findClosestCell(constraint, x + 1, y, visited, xOut, yOut)
		|| _findClosestCell(constraint, x - 1, y, visited, xOut, yOut)
		|| _findClosestCell(constraint, x, y + 1, visited, xOut, yOut)
		|| _findClosestCell(constraint, x, y - 1, visited, xOut, yOut);
}

void MapGenerator::_dispatchEnemies(const int nbMaxEnemies) {
	for (int i = 0; i < nbMaxEnemies; ++i) {
		int x = rand() % m_map.getWidth(),
			y = rand() % m_map.getHeight();

		std::vector<bool> visited((size_t) (m_map.getWidth() * m_map.getHeight()), false);
		_findClosestCell(CURRENT_CELL_IS_WALKABLE | CURRENT_CELL_IS_RIM, x, y, visited, x, y);
		m_map.addEnemySpawnableCell((char) x, (char) y);
	}
}

void MapGenerator::_addStair(int direction, int x, int y) {
	if (direction == STAIR_UP && m_map.getLevel() == 0) {
		return;
	}

	if (x < 0 || y < 0) {
		x = rand() % m_map.getWidth();
		y = rand() % m_map.getHeight();
		std::vector<bool> visited((size_t) (m_map.getWidth() * m_map.getHeight()), false);
		_findClosestCell(CURRENT_CELL_IS_WALKABLE | CURRENT_CELL_IS_RIM, x, y, visited, x, y);
	}

	S_MapChangeEventData event;
	strncpy(event.mapName, m_map.getName().c_str(), MAX_LENGTH_MAP_NAME);
	event.mapLevel = m_map.getLevel() + direction;
	m_map.addEvent(x, y, event);
	m_map.addObject(x, y, direction == STAIR_UP ? OBJECT_STAIR_UP : OBJECT_STAIR_DOWN);
}

void MapGenerator::_addEntrance() {
	int x = rand() % m_map.getWidth();
	int y = rand() % m_map.getHeight();
	std::vector<bool> visited((size_t) (m_map.getWidth() * m_map.getHeight()), false);
	_findClosestCell(CURRENT_CELL_IS_RIM, x, y, visited, x, y);

	m_map.addObject(x, y, OBJECT_EXIT);
}

void MapGenerator::_addCaveArtifact() {
	int x = rand() % m_map.getWidth(),
		y = rand() % m_map.getHeight();

	std::vector<bool> visited((size_t) (m_map.getWidth() * m_map.getHeight()), false);
	_findClosestCell(CURRENT_CELL_IS_WALKABLE, x, y, visited, x, y);
	m_map.addObject(x, y, ITEM_SCROLL);
}
