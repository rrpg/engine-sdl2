#include "Map.hpp"
#include <algorithm>
#include "SDL2_framework/Game.h"
#include "Parser/Tile.hpp"

MyUnorderedMap<E_MapType, std::vector<S_EnemyProbability>> Map::s_mEnemiesPerMapType = MyUnorderedMap<E_MapType, std::vector<S_EnemyProbability>>({});

void Map::_initEnemiesPerMapType() {
	s_mEnemiesPerMapType[DEFAULT] = {};
	s_mEnemiesPerMapType[CAVE] = {{RACE_DEMON, 0, 1}, {RACE_HUMAN, 2, 250}, {RACE_RAT, 251, 1000}};
}

Map::Map() :
	m_vGrid({}),
	m_mTerrains({}),
	m_mTerrainsTileData({}),
	m_mActors({}),
	m_vEnemySpawnableCells({}) {
}

Map::Map(const Map &r) :
	m_type(r.m_type),
	m_iWidth(r.m_iWidth),
	m_iHeight(r.m_iHeight),
	m_iDisplayTileWidth(r.m_iDisplayTileWidth),
	m_iDisplayTileHeight(r.m_iDisplayTileHeight),
	m_sStartPoint(r.m_sStartPoint),
	m_vGrid(r.m_vGrid),
	m_mTerrains({}),
	m_mTerrainsTileData(r.m_mTerrainsTileData),
	m_mActors(r.m_mActors),
	m_mEvents(r.m_mEvents),
	m_vEnemySpawnableCells(r.m_vEnemySpawnableCells)
{
}

Map & Map::operator=(const Map &r) {
	// check for "self assignment" and do nothing in that case
	if (this == &r) {
		return *this;
	}

	m_type = r.m_type;
	m_iWidth = r.m_iWidth;
	m_iHeight = r.m_iHeight;
	m_iDisplayTileWidth = r.m_iDisplayTileWidth;
	m_iDisplayTileHeight = r.m_iDisplayTileHeight;
	m_sStartPoint = r.m_sStartPoint;
	m_vGrid = r.m_vGrid;
	m_mTerrains = {};
	m_mTerrainsTileData = r.m_mTerrainsTileData;
	m_mActors = r.m_mActors;
	m_mEvents = r.m_mEvents;
	m_vEnemySpawnableCells = r.m_vEnemySpawnableCells;
	return *this;
}

Map::~Map() {
	m_vGrid.clear();
	m_mTerrainsTileData.clear();
	m_vEnemySpawnableCells.clear();
	for (auto actor : m_mActors) {
		delete actor.second;
	}
	for (auto terrain : m_mTerrains) {
		delete terrain.second;
	}
	for (auto event : m_mEvents) {
		delete event.second.second;
	}
	m_mActors.clear();
	m_mTerrains.clear();
	m_mEvents.clear();

	if (m_tilesFile != 0) {
		fclose(m_tilesFile);
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
	m_tilesFile = fopen(tilesFilePath, "r");
}

void Map::clearDeadActors() {
	for (auto it = m_mActors.begin(); it != m_mActors.end();) {
		if (it->second->isDead()) {
			delete it->second;
			it = m_mActors.erase(it);
		}
		else {
			++it;
		}
	}
}

std::string Map::_getCoordsKey(int x, int y) {
	char xStr[100], yStr[100];
	sprintf(xStr, "%d", x);
	sprintf(yStr, "%d", y);
	return std::string(xStr) + "-" + std::string(yStr);
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

void Map::setDisplayTileDimensions(int w, int h) {
	m_iDisplayTileWidth = w;
	m_iDisplayTileHeight = h;
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

S_TileData Map::_getTerrainTileData(const E_TerrainTile tile) {
	if (m_tilesFile != 0 && m_mTerrainsTileData.find(tile) == m_mTerrainsTileData.end()) {
		S_TileData tileData;
		TileParser::getTileInfo(tileData, m_tilesFile, (int) tile);
		m_mTerrainsTileData[tile] = tileData;
	}
	return m_mTerrainsTileData[tile];
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

int Map::getDisplayTileWidth() {
	return m_iDisplayTileWidth;
}

int Map::getDisplayTileHeight() {
	return m_iDisplayTileHeight;
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

		Actor* enemy = actorFactory.createEnemy(enemyClass->race);
		enemy->setX(enemySpawnCell.first);
		enemy->setY(enemySpawnCell.second);
		addActor(enemy);
	}
}

Vector2D Map::getStartPoint() {
	return m_sStartPoint;
}

void Map::addActor(Actor *actor) {
	std::string key = _getCoordsKey(actor->getX(), actor->getY());
	m_mActors[key] = actor;
}

int Map::_getSameNeighbours(int x, int y) {
	E_TerrainType type = getTile(x, y);
	int nbNeighbours = (y == 0 || getTile(x, y - 1) == type) // north
		+ 2 * (x == 0 || getTile(x - 1, y) == type) // west
		+ (1 << 2) * (x == m_iWidth - 1 || getTile(x + 1, y) == type) // east
		+ (1 << 3) * (y == m_iHeight - 1 || getTile(x, y + 1) == type); // south

	return nbNeighbours;
}

void Map::render(SDL_Rect camera, int centerX, int centerY) {
	// x,y coords in the grid
	int cameraWidthGrid = camera.w / m_iDisplayTileWidth,
		cameraHeightGrid = camera.h / m_iDisplayTileHeight;

	SDL_Rect visibleArea = {
		// portion of the map which is visible
		centerX - cameraWidthGrid / 2,
		centerY - cameraHeightGrid / 2,
		cameraWidthGrid,
		cameraHeightGrid
	};

	Vector2D shift = {
		(float) (visibleArea.x * m_iDisplayTileWidth),
		(float) (visibleArea.y * m_iDisplayTileHeight)
	};

	_renderTerrain(camera, visibleArea, shift);
	_renderActors(camera, visibleArea, shift);
}

void Map::_renderTerrain(SDL_Rect camera, SDL_Rect visibleArea, Vector2D shift) {
	// camera is in pixels in the window
	TextureManager *manager = TextureManager::Instance();
	Game *game = Game::Instance();

	int shiftX = (int) shift.getX();
	int shiftY = (int) shift.getY();
	for (int y = visibleArea.y; y < visibleArea.y + visibleArea.h; ++y) {
		for (int x = visibleArea.x; x < visibleArea.x + visibleArea.w; ++x) {
			if (!areCoordinatesValid(x, y)) {
				continue;
			}

			E_TerrainType type = getTile(x, y);
			Terrain *terrain = _getTerrain(type);
			E_TerrainTile tile = Terrain::getTerrainTile(
				type,
				terrain->hasFlag(Terrain::TERRAIN_FLAG_BASE) ?
					15 : _getSameNeighbours(x, y)
			);
			S_TileData tileData = _getTerrainTileData(tile);
			int xScreen = x * tileData.width - shiftX + camera.x,
				yScreen = y * tileData.height - shiftY + camera.y;

			manager->load(tileData.tileset, game->getRenderer());
			// the rows are 1 based, and the columns are 0 based, which is
			// stupid
			manager->drawTile(
				tileData.tileset,
				0, // margin
				0, // spacing
				xScreen,
				yScreen,
				tileData.width,
				tileData.height,
				tileData.y + 1,
				tileData.x,
				game->getRenderer()
			);
		}
	}
}

void Map::_renderActors(SDL_Rect camera, SDL_Rect visibleArea, Vector2D shift) {
	int displayShiftX = camera.x - (int) shift.getX();
	int displayShiftY = camera.y - (int) shift.getY();
	for (auto actor : m_mActors) {
		if ((visibleArea.x > 0 && actor.second->getX() < visibleArea.x)
				|| actor.second->getX() > (visibleArea.x + visibleArea.w)
			|| (visibleArea.y > 0 && actor.second->getY() < visibleArea.y)
				|| actor.second->getY() > (visibleArea.y + visibleArea.h)
		) {
			continue;
		}

		actor.second->render(
			displayShiftX,
			displayShiftY
		);
	}
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
	return isWalkable;
}

bool Map::isCellObstructingView(int x, int y) {
	return _getTerrain(getTile(x, y))->hasFlag(
		Terrain::TERRAIN_FLAG_OBSTRUCTING_VIEW
	);
}

std::unordered_map<std::string, Actor*> &Map::getActors() {
	return m_mActors;
}

Actor *Map::getActorAt(int x, int y) {
	std::string key = _getCoordsKey(x, y);
	auto it = m_mActors.find(key);
	if (it != m_mActors.end()) {
		return it->second;
	}

	return NULL;
}

bool Map::moveActor(Actor *a, int newX, int newY) {
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

MapEvent* Map::getEvent(const int x, const int y) const {
	std::string key = _getCoordsKey(x, y);
	auto it = m_mEvents.find(key);
	if (it != m_mEvents.end()) {
		return it->second.second;
	}

	return NULL;
}

void Map::addEvent(int x, int y, MapEvent *event) {
	t_coordinates coords = {x, y};
	m_mEvents[_getCoordsKey(x, y)] = std::make_pair(coords, event);
}

std::unordered_map<std::string, std::pair<t_coordinates, MapEvent*>> Map::getEvents() {
	return m_mEvents;
}
