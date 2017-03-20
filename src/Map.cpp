#include "Map.hpp"

#include "SDL2_framework/Game.h"
#include "Parser/Map.hpp"

const int CELL_FLAG_WALKABLE = 0x1;
const int CELL_FLAG_OBSTRUCTING_VIEW = 0x2;

Map::Map() {
	m_mCellTypeFlags[Wall] = CELL_FLAG_OBSTRUCTING_VIEW;
	m_mCellTypeFlags[Path] = CELL_FLAG_WALKABLE;
	m_mCellTypeFlags[Grass] = CELL_FLAG_WALKABLE;
}

Map::~Map() {
	for (auto actor : m_mActors) {
		delete actor.second;
	}
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

std::string Map::getCoordsKey(int x, int y) {
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

void Map::setTileset(Tileset tileset) {
	m_tileset = tileset;
}

E_FileParsingResult Map::setMap(const char* mapFile) {
	MapParser parser = MapParser(*this);
	E_FileParsingResult result = parser.parseFile(mapFile);
	return result;
}

std::vector<int>* Map::getGrid() {
	return &m_vGrid;
}

void Map::addEnemySpawnableCell(int cellIndex) {
	m_vEnemySpawnableCells.push_back(cellIndex);
}

void Map::initEnemies(ActorFactory &actorFactory) {
	for (auto enemySpawnCell : m_vEnemySpawnableCells) {
		Actor* enemy = actorFactory.createRandomFoe();
		enemy->setX(enemySpawnCell % m_iWidth);
		enemy->setY(enemySpawnCell / m_iWidth);
		addActor(enemy);
	}
}

Vector2D Map::getStartPoint() {
	return m_sStartPoint;
}

void Map::addActor(Actor *actor) {
	std::string key = getCoordsKey(actor->getX(), actor->getY());
	m_mActors[key] = actor;
}

void Map::render(SDL_Rect camera, int centerX, int centerY) {
	// x,y coords in the grid
	int cameraWidthGrid = camera.w / m_tileset.tileWidth,
		 cameraHeightGrid = camera.h / m_tileset.tileHeight;

	SDL_Rect visibleArea = {
		// portion of the map which is visible
		centerX - cameraWidthGrid / 2,
		centerY - cameraHeightGrid / 2,
		cameraWidthGrid,
		cameraHeightGrid
	};

	Vector2D shift = {
		(float) (visibleArea.x * m_tileset.tileWidth),
		(float) (visibleArea.y * m_tileset.tileHeight)
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
			if (x < 0 || x >= (signed) m_iWidth || y < 0 || y >= (signed) m_iHeight) {
				continue;
			}
			int cell = m_vGrid[y * m_iWidth + x];
			int xScreen, yScreen;
			xScreen = x * m_tileset.tileWidth - shiftX + camera.x;
			yScreen = y * m_tileset.tileHeight - shiftY + camera.y;

			// the rows are 1 based, and the columns are 0 based, which is
			// stupid
			int tilesetRow = 1 + (cell / m_tileset.numColumns),
				tilesetCol = cell % m_tileset.numColumns;
			manager->drawTile(
				m_tileset.name,
				0, // margin
				0, // spacing
				xScreen,
				yScreen,
				m_tileset.tileWidth,
				m_tileset.tileHeight,
				tilesetRow,
				tilesetCol,
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
		xScreen = actor.second->getX() * m_tileset.tileWidth - shiftX + camera.x;
		yScreen = actor.second->getY() * m_tileset.tileHeight - shiftY + camera.y;
		manager->drawTile(
			actor.second->getRace().getTilesetName(),
			0, // margin
			0, // spacing
			xScreen,
			yScreen,
			m_tileset.tileWidth,
			m_tileset.tileHeight,
			(int) actor.second->getRace().getSpriteY() + 1,
			(int) actor.second->getRace().getSpriteX(),
			game->getRenderer()
		);

		// render HPs
		SDL_Rect r;
		r.x = xScreen;
		r.y = yScreen;
		r.w = m_tileset.tileWidth * actor.second->getHealth() / actor.second->getMaxHealth();
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
	E_CellType cellType = (E_CellType) m_vGrid[gridIndex];
	bool hasWalkableFlag = (m_mCellTypeFlags[cellType] & CELL_FLAG_WALKABLE) == CELL_FLAG_WALKABLE;
	bool hasActorOnCell;
	auto got = m_mActors.find(getCoordsKey(x, y));
	hasActorOnCell = got != m_mActors.end();
	return hasWalkableFlag && !hasActorOnCell;
}

bool Map::isCellObstructingView(int x, int y) {
	int gridIndex = y * m_iWidth + x;
	E_CellType cellType = (E_CellType) m_vGrid[gridIndex];
	return (m_mCellTypeFlags[cellType] & CELL_FLAG_OBSTRUCTING_VIEW) == CELL_FLAG_OBSTRUCTING_VIEW;
}

std::unordered_map<std::string, Actor*> &Map::getActors() {
	return m_mActors;
}

Actor *Map::getActorAt(int x, int y) {
	std::string key = getCoordsKey(x, y);
	auto it = m_mActors.find(key);
	if (it != m_mActors.end()) {
		return it->second;
	}

	return NULL;
}

void Map::moveActor(Actor *a, int newX, int newY) {
	std::string key = getCoordsKey(a->getX(), a->getY());
	std::string newKey = getCoordsKey(newX, newY);
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
