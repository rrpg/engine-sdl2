#include "Map.hpp"
#include "Object.hpp"
#include "ActorFactory.hpp"
#include "Actor.hpp"
#include <algorithm>
#include <sstream>
#include <string>
#include "SDL2_framework/Game.h"

MyUnorderedMap<E_MapType, std::vector<S_EnemyProbability>> Map::s_mEnemiesPerMapType = MyUnorderedMap<E_MapType, std::vector<S_EnemyProbability>>({});

void Map::_initEnemiesPerMapType() {
	s_mEnemiesPerMapType[DEFAULT] = {};
	s_mEnemiesPerMapType[CAVE] = {{RACE_DEMON, 0, 1}, {RACE_HUMAN, 2, 250}, {RACE_RAT, 251, 1000}};
}

Map::Map() :
	m_sStartPoint(Vector2D()),
	m_vGrid({}),
	m_mTerrains({}),
	m_mTerrainsTileData({}),
	m_mActors({}),
	m_mEvents({}),
	m_mMapJunctions({}),
	m_mObjects({}),
	m_vEnemySpawnableCells({}),
	m_tilesManager(ResourceManager<S_TileData>()),
	m_objectsManager(ResourceManager<S_ObjectData>()) {
}

Map::~Map() {
	clear();
}

void Map::clear() {
	m_vGrid.clear();
	m_mTerrainsTileData.clear();
	m_vEnemySpawnableCells.clear();
	for (auto terrain : m_mTerrains) {
		delete terrain.second;
	}
	m_mActors.clear();
	m_mTerrains.clear();
	m_mEvents.clear();
	m_mObjects.clear();
}

std::string Map::getKeyName(std::string name, int level) {
	std::ostringstream os;
	if (name == "" || level == -1) {
		os << m_iLevel;
		return m_sName + "-" + os.str();
	}
	else {
		os << level;
		return name + "-" + os.str();
	}
}

void Map::setName(std::string name) {
	m_sName = name;
}

void Map::setLevel(int level) {
	m_iLevel = level;
}

std::string Map::getName() {
	return m_sName;
}

int Map::getLevel() {
	return m_iLevel;
}

void Map::setTileFile(const char *tilesFilePath) {
	m_tilesManager.setResourceFile(tilesFilePath);
}

void Map::setObjectsFile(const char *objectsFilePath) {
	m_objectsManager.setResourceFile(objectsFilePath);
}

void Map::clearDeadActors() {
	for (auto it = m_mActors.begin(); it != m_mActors.end();) {
		if (it->second->isDead()) {
			it = m_mActors.erase(it);
		}
		else {
			++it;
		}
	}
}

std::string Map::_getCoordsKey(int x, int y) {
	char key[100];
	sprintf(key, "%d-%d", x, y);
	return key;
}

void Map::setType(E_MapType type) {
	m_type = type;
}

E_MapType Map::getType() {
	return m_type;
}

void Map::setStartPoint(float x, float y) {
	m_sStartPoint.setX(x);
	m_sStartPoint.setY(y);
}

void Map::setDimensions(int w, int h) {
	m_iWidth = w;
	m_iHeight = h;
}

Terrain *Map::_getTerrain(E_TerrainType type) {
	if (m_mTerrains.find(type) == m_mTerrains.end()) {
		Terrain *terrain = new Terrain();
		if (TERRAIN_GRASS_NORMAL == type) {
			terrain->setFlags(Terrain::TERRAIN_FLAG_WALKABLE);
		}
		else if (TERRAIN_SOIL_NORMAL == type) {
			terrain->setFlags(
				Terrain::TERRAIN_FLAG_WALKABLE | Terrain::TERRAIN_FLAG_BASE
			);
		}
		else if (TERRAIN_ROCK_NORMAL == type) {
			terrain->setFlags(Terrain::TERRAIN_FLAG_OBSTRUCTING_VIEW);
		}

		m_mTerrains[type] = terrain;
	}

	return m_mTerrains[type];
}

S_TileData Map::getTerrainTileData(int visibleNeighbours, int x, int y) {
	E_TerrainType type = getTile(x, y);
	Terrain *terrain = _getTerrain(type);
	E_TerrainTile tile = Terrain::getTerrainTile(
		type,
		terrain->hasFlag(Terrain::TERRAIN_FLAG_BASE) ?
			15 : _getSameNeighbours(x, y) | visibleNeighbours
	);
	if (m_mTerrainsTileData.find(tile) == m_mTerrainsTileData.end()) {
		S_TileData tileData;
		m_tilesManager.getResource(tile, tileData);
		m_mTerrainsTileData[tile] = tileData;
	}
	return m_mTerrainsTileData[tile];
}

S_ObjectData Map::getObjectData(const E_Object objectType) {
	S_ObjectData objectData;
	m_objectsManager.getResource(objectType, objectData);
	return objectData;
}

void Map::initializeGrid(E_TerrainType type) {
	int size = m_iWidth * m_iHeight;
	for (int c = 0; c < size; ++c) {
		m_vGrid.push_back(type);
	}
}

void Map::setTile(int x, int y, E_TerrainType type) {
	m_vGrid[getTileIndex(x, y)] = type;
}

std::vector<E_TerrainType>* Map::getGrid() {
	return &m_vGrid;
}

void Map::setGrid(std::vector<E_TerrainType> grid) {
	m_vGrid = grid;
}

E_TerrainType Map::getTile(int x, int y) {
	return m_vGrid[getTileIndex(x, y)];
}

size_t Map::getTileIndex(int x, int y) {
	return (size_t) (y * m_iWidth + x);
}

int Map::getWidth() {
	return m_iWidth;
}

int Map::getHeight() {
	return m_iHeight;
}

void Map::addEnemySpawnableCell(char x, char y) {
	m_vEnemySpawnableCells.push_back(std::make_pair(x, y));
}

std::vector<t_coordinates> Map::getEnemySpawnableCells() {
	return m_vEnemySpawnableCells;
}

void Map::initEnemies(ActorFactory &actorFactory) {
	if (s_mEnemiesPerMapType.empty()) {
		Map::_initEnemiesPerMapType();
	}
	for (auto enemySpawnCell : m_vEnemySpawnableCells) {
		int enemyProba = rand() % 1000;
		auto enemyClass = std::find_if(
			s_mEnemiesPerMapType[m_type].begin(),
			s_mEnemiesPerMapType[m_type].end(),
			[&] (const S_EnemyProbability & p) {
				return p.probaRangeFrom <= enemyProba && enemyProba <= p.probaRangeTo;
			}
		);

		if (enemyClass == s_mEnemiesPerMapType[m_type].end()) {
			enemyClass = s_mEnemiesPerMapType[m_type].begin();
		}

		std::shared_ptr<Actor> enemy = actorFactory.createEnemy(enemyClass->race);
		enemy->setX(enemySpawnCell.first);
		enemy->setY(enemySpawnCell.second);
		addActor(enemy);
	}
}

Vector2D Map::getStartPoint() {
	return m_sStartPoint;
}

void Map::addActor(std::shared_ptr<Actor> actor) {
	std::string key = _getCoordsKey(actor->getX(), actor->getY());
	m_mActors[key] = actor;
}

int Map::_getSameNeighbours(int x, int y) {
	E_TerrainType type = getTile(x, y);
	int nbNeighbours = (y == 0 || getTile(x, y - 1) == type) // north
		+ NEIGHBOUR_WEST * (x == 0 || getTile(x - 1, y) == type) // west
		+ NEIGHBOUR_EAST * (x == m_iWidth - 1 || getTile(x + 1, y) == type) // east
		+ NEIGHBOUR_SOUTH * (y == m_iHeight - 1 || getTile(x, y + 1) == type); // south

	return nbNeighbours;
}

bool Map::areCoordinatesValid(int x, int y) {
	return x >= 0 && y >= 0 && x < m_iWidth && y < m_iHeight;
}

bool Map::isCellWalkable(int x, int y, unsigned int walkableConstraint) {
	if (!areCoordinatesValid(x, y)) {
		return false;
	}

	bool isWalkable = _getTerrain(getTile(x, y))->hasFlag(
		Terrain::TERRAIN_FLAG_WALKABLE
	);

	if (walkableConstraint & WALKABLE_CONSTRAINT_ACTOR_IS_BLOCKING) {
		bool hasActorOnCell;
		auto got = m_mActors.find(_getCoordsKey(x, y));
		hasActorOnCell = got != m_mActors.end();
		isWalkable &= !hasActorOnCell;
	}

	if (walkableConstraint & WALKABLE_CONSTRAINT_ACTOR_SPAWN_LOCATION) {
		auto spawnableCell = std::find(
			m_vEnemySpawnableCells.begin(),
			m_vEnemySpawnableCells.end(),
			std::make_pair(x, y)
		);
		isWalkable &= spawnableCell == m_vEnemySpawnableCells.end();
	}

	//test if there is a non walkable object here
	E_Object *object = getObjectAt(x, y);
	if (object != NULL) {
		S_ObjectData data = getObjectData(*object);
		isWalkable &= data.flags & OBJECT_FLAG_WALKABLE;
	}

	return isWalkable;
}

bool Map::isCellObstructingView(int x, int y) {
	return _getTerrain(getTile(x, y))->hasFlag(
		Terrain::TERRAIN_FLAG_OBSTRUCTING_VIEW
	);
}

std::unordered_map<std::string, std::shared_ptr<Actor>> &Map::getActors() {
	return m_mActors;
}

std::shared_ptr<Actor> Map::getActorAt(int x, int y) {
	std::string key = _getCoordsKey(x, y);
	auto it = m_mActors.find(key);
	if (it != m_mActors.end()) {
		return it->second;
	}

	return NULL;
}

bool Map::moveActor(Actor* a, int newX, int newY) {
	if (!isCellWalkable(newX, newY, WALKABLE_CONSTRAINT_ACTOR_IS_BLOCKING)) {
		return false;
	}

	std::string key = _getCoordsKey(a->getX(), a->getY());
	std::string newKey = _getCoordsKey(newX, newY);
	auto it = m_mActors.find(key);
	if (it != m_mActors.end()) {
		it->second->setX(newX);
		it->second->setY(newY);
		// Swap value from oldKey to newKey, note that a default constructed value
		// is created by operator[] if 'm_mActors' does not contain newKey.
		std::swap(m_mActors[newKey], it->second);

		// Erase old key-value from map
		m_mActors.erase(it);
	}

	return true;
}

bool Map::hasEvent(const int x, const int y) {
	std::string key = _getCoordsKey(x, y);
	auto it = m_mEvents.find(key);
	return it != m_mEvents.end();
}

S_MapChangeEventData Map::getEvent(const int x, const int y) {
	std::string key = _getCoordsKey(x, y);
	auto it = m_mEvents.find(key);
	return it->second.second;
}

void Map::addEvent(int x, int y, S_MapChangeEventData event) {
	t_coordinates coords = {x, y};
	m_mEvents[_getCoordsKey(x, y)] = std::make_pair(coords, event);
	m_mMapJunctions[getKeyName(event.mapName, event.mapLevel)] = coords;
}

std::unordered_map<std::string, std::pair<t_coordinates, S_MapChangeEventData>> &Map::getEvents() {
	return m_mEvents;
}

t_coordinates *Map::getMapJunction(std::string mapKeyName) {
	auto it = m_mMapJunctions.find(mapKeyName);
	if (it == m_mMapJunctions.end()) {
		return NULL;
	}

	return &it->second;
}

void Map::addObject(int x, int y, E_Object object) {
	t_coordinates coords = {x, y};
	m_mObjects[_getCoordsKey(x, y)] = std::make_pair(coords, object);
}

std::unordered_map<std::string, std::pair<t_coordinates, E_Object>> Map::getObjects() {
	return m_mObjects;
}

E_Object *Map::getObjectAt(int x, int y) {
	std::string key = _getCoordsKey(x, y);
	auto it = m_mObjects.find(key);
	if (it != m_mObjects.end()) {
		return &it->second.second;
	}

	return NULL;
}
