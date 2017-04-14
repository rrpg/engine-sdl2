#include "Map.hpp"

#include "SDL2_framework/Game.h"
#include "Parser/Tile.hpp"

Map::~Map() {
	for (auto actor : m_mActors) {
		delete actor.second;
	}
	for (auto terrain : m_mTerrains) {
		delete terrain.second;
	}

	if (m_tilesFile != 0) {
		fclose(m_tilesFile);
	}
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
	return std::to_string(x) + "-" + std::to_string(y);
}

void Map::setStartPoint(float x, float y) {
	m_sStartPoint.setX(x);
	m_sStartPoint.setY(y);
}

void Map::setDimensions(unsigned int w, unsigned int h) {
	m_iWidth = w;
	m_iHeight = h;
}

void Map::setDisplayTileDimensions(unsigned int w, unsigned int h) {
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
	unsigned int size = m_iWidth * m_iHeight;
	for (unsigned int c = 0; c < size; ++c) {
		m_vGrid.push_back(type);
	}
}

void Map::setTile(int x, int y, E_TerrainType type) {
	int gridIndex = y * m_iWidth + x;
	m_vGrid[gridIndex] = type;
}

std::vector<E_TerrainType>* Map::getGrid() {
	return &m_vGrid;
}

void Map::setGrid(std::vector<E_TerrainType> grid) {
	m_vGrid = grid;
}

E_TerrainType Map::getTile(int x, int y) {
	return m_vGrid[y * m_iWidth + x];
}

unsigned int Map::getWidth() {
	return m_iWidth;
}

unsigned int Map::getHeight() {
	return m_iHeight;
}

unsigned int Map::getDisplayTileWidth() {
	return m_iDisplayTileWidth;
}

unsigned int Map::getDisplayTileHeight() {
	return m_iDisplayTileHeight;
}

void Map::addEnemySpawnableCell(char x, char y) {
	m_vEnemySpawnableCells.push_back(std::make_pair(x, y));
}

std::vector<std::pair<char, char>> Map::getEnemySpawnableCells() {
	return m_vEnemySpawnableCells;
}

void Map::initEnemies(ActorFactory &actorFactory) {
	for (auto enemySpawnCell : m_vEnemySpawnableCells) {
		Actor* enemy = actorFactory.createRandomFoe();
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

int Map::_getSameNeighbours(unsigned int x, unsigned int y) {
	E_TerrainType type = getTile(x, y);
	// north
	return (y == 0 || getTile(x, y - 1) == type)
		// west
		+ 2 * (x == 0 || getTile(x - 1, y) == type)
		// east
		+ (1 << 2) * (x == m_iWidth || getTile(x + 1, y) == type)
		// south
		+ (1 << 3) * (y == m_iHeight || getTile(x, y + 1) == type);
}

void Map::_renderTerrain(SDL_Rect camera, SDL_Rect visibleArea, Vector2D shift) {
	// camera is in pixels in the window
	TextureManager *manager = TextureManager::Instance();
	Game *game = Game::Instance();

	int shiftX = (int) shift.getX();
	int shiftY = (int) shift.getY();
	for (int y = visibleArea.y; y < visibleArea.y + visibleArea.h; ++y) {
		for (int x = visibleArea.x; x < visibleArea.x + visibleArea.w; ++x) {
			if (x < 0 || x >= (signed) m_iWidth || y < 0 || y >= (signed) m_iHeight) {
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
	TextureManager *manager = TextureManager::Instance();
	Game *game = Game::Instance();

	int shiftX = (int) shift.getX();
	int shiftY = (int) shift.getY();
	for (auto actor : m_mActors) {
		if (actor.second->getX() < visibleArea.x || actor.second->getX() > visibleArea.x + visibleArea.w
			|| actor.second->getY() < visibleArea.y || actor.second->getY() > visibleArea.y + visibleArea.h
		) {
			continue;
		}

		int xScreen, yScreen;
		xScreen = actor.second->getX() * m_iDisplayTileWidth - shiftX + camera.x;
		yScreen = actor.second->getY() * m_iDisplayTileHeight - shiftY + camera.y;
		manager->drawTile(
			actor.second->getRace().getTilesetName(),
			0, // margin
			0, // spacing
			xScreen,
			yScreen,
			m_iDisplayTileWidth,
			m_iDisplayTileHeight,
			(int) actor.second->getRace().getSpriteY() + 1,
			(int) actor.second->getRace().getSpriteX(),
			game->getRenderer()
		);

		// render HPs
		SDL_Rect r;
		r.x = xScreen;
		r.y = yScreen;
		r.w = m_iDisplayTileWidth * actor.second->getHealth() / actor.second->getMaxHealth();
		r.h = 2;
		SDL_SetRenderDrawColor(game->getRenderer(), 0xff, 0, 0, 255);
		SDL_RenderFillRect(game->getRenderer(), &r);
	}
}

bool Map::isCellWalkable(int x, int y) {
	if (x < 0 || x >= (signed) m_iWidth || y < 0 || y >= (signed) m_iHeight) {
		return false;
	}

	int gridIndex = y * m_iWidth + x;
	bool hasWalkableFlag = _getTerrain(m_vGrid[gridIndex])->hasFlag(
		Terrain::TERRAIN_FLAG_WALKABLE
	);
	bool hasActorOnCell;
	auto got = m_mActors.find(_getCoordsKey(x, y));
	hasActorOnCell = got != m_mActors.end();
	return hasWalkableFlag && !hasActorOnCell;
}

bool Map::isCellObstructingView(int x, int y) {
	int gridIndex = y * m_iWidth + x;
	return _getTerrain(m_vGrid[gridIndex])->hasFlag(
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

void Map::moveActor(Actor *a, int newX, int newY) {
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
}