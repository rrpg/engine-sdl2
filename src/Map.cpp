#include "Map.hpp"

#include <string.h>
#include <fstream>
#include <libgen.h>
#include "SDL2_framework/TextureManager.h"
#include "SDL2_framework/Game.h"

const int MAX_CHARS_PER_LINE = 1024;
const int MAX_CHAR_TILESET_NAME = 100;
const int MAX_CHAR_TILESET_FILE = 100;

const int CELL_FLAG_WALKABLE = 0x1;

Map::Map() {
	m_mCellTypeFlags[Wall] = 0;
	m_mCellTypeFlags[Path] = CELL_FLAG_WALKABLE;
	m_mCellTypeFlags[Grass] = CELL_FLAG_WALKABLE;
}

std::string Map::getCoordsKey(int x, int y) {
	return std::to_string(x) + "-" + std::to_string(y);
}

E_MapParsingResult Map::setMap(const char* mapFile) {
	std::ifstream fin;
	fin.open(mapFile);
	if (!fin.good()) {
		fin.close();
		return ERROR_OPENING_FILE;
	}

	E_MapParsingResult retValue = OK;
	char *mapDir = dirname(const_cast<char*>(mapFile));
	while (!fin.eof()) {
		char buf[MAX_CHARS_PER_LINE];
		// @check too long lines
		fin.getline(buf, MAX_CHARS_PER_LINE);

		if (buf[0] == '\0' || buf[0] == '#') {
			continue;
		}

		retValue = _parseLine(mapDir, buf);
		if (retValue != OK) {
			break;
		}
	}

	fin.close();
	return retValue;
}

E_MapParsingResult Map::_parseLine(const char *mapDir, const char *line) {
	int retValue = OK,
		sscanfResult;
	char type;

	if (strlen(line) < 3) {
		return INVALID_LINE_FORMAT;
	}

	type = *line;
	line += 2;
	switch (type) {
		case 'd':
			sscanfResult = sscanf(line, "%u %u\n", &m_iWidth, &m_iHeight);
			if (sscanfResult != 2) {
				retValue = INVALID_DIMENSIONS_FORMAT;
			}
			break;
		case 'c':
			_parseMapContent(line);
			break;
		case 't':
			retValue = _parseTileset(mapDir, line);
			break;
		case 's':
			int x, y;
			sscanfResult = sscanf(
				line,
				"%d %d\n",
				&x, &y
			);
			if (sscanfResult != 2) {
				retValue = INVALID_START_POINT_FORMAT;
			}
			m_sStartPoint.setX((float) x);
			m_sStartPoint.setY((float) y);
			break;
		default:
			break;
	}

	return (E_MapParsingResult) retValue;
}

void Map::_parseMapContent(const char *line) {
	while (*line != '\n' && *line != '\0') {
		uint32_t cellInfo = *line - '0';
		bool canSpawnEnemy = cellInfo & 0x1;
		uint8_t cellTile = (cellInfo >> 0x1) & 255;
		// the an enemy can spawn on the cell
		if (canSpawnEnemy) {
			m_vEnemySpawnableCells.push_back((int) m_vGrid.size());
		}

		m_vGrid.push_back(cellTile);
		++line;
	}
}

E_MapParsingResult Map::_parseTileset(const char *mapDir, const char *line) {
	Tileset tileset;
	char tilesetPath[MAX_CHAR_TILESET_FILE],
		 tilesetName[MAX_CHAR_TILESET_NAME];
	unsigned int tilesetWidth, tileSize;
	// format is:
	// tilesetname filepath tilesize tilesetwidth
	int res = sscanf(
		line,
		"%s %s %u %u",
		tilesetName, tilesetPath, &tileSize, &tilesetWidth
	);

	if (res != 4) {
		return INVALID_TILESET_DEFINITION;
	}

	m_tileset.name = tilesetName;
	std::string textureFile = std::string(mapDir) + "/" + tilesetPath;

	// first add the tileset to texture manager
	TextureManager::Instance()->load(
		textureFile,
		m_tileset.name,
		Game::Instance()->getRenderer()
	);

	m_tileset.tileWidth = tileSize;
	m_tileset.tileHeight = tileSize;
	m_tileset.width = tileSize * tilesetWidth;
	m_tileset.name = tilesetName;
	m_tileset.numColumns = tilesetWidth;
	return OK;
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
			m_tileset.name,
			0, // margin
			0, // spacing
			xScreen,
			yScreen,
			m_tileset.tileWidth,
			m_tileset.tileHeight,
			actor.second->getTilesetRowIndex() + 1,
			actor.second->getFrame(),
			game->getRenderer()
		);
	}
}

bool Map::isCellWalkable(int x, int y) {
	if (x < 0 || x >= (signed) m_iWidth || y < 0 || y >= (signed) m_iHeight) {
		return false;
	}

	int gridIndex = y * m_iWidth + x;
	E_CellType cellType = (E_CellType) m_vGrid[gridIndex];
	return (m_mCellTypeFlags[cellType] & CELL_FLAG_WALKABLE) == CELL_FLAG_WALKABLE;
}
