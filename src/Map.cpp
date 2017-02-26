#include "Map.hpp"

#include <string.h>
#include <fstream>
#include <libgen.h>
#include "SDL2_framework/TextureManager.h"
#include "SDL2_framework/Game.h"

const int MAX_CHARS_PER_LINE = 1024;
const int MAX_CHAR_TILESET_NAME = 100;
const int MAX_CHAR_TILESET_FILE = 100;

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
		default:
			break;
	}

	return (E_MapParsingResult) retValue;
}

void Map::_parseMapContent(const char *line) {
	while (*line != '\n' && *line != '\0') {
		m_vGrid.push_back(*line - '0');
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

void Map::addActor(Actor *actor) {
	m_vActors.push_back(actor);
}

void Map::render(SDL_Rect camera, int center) {
	// camera is in pixels in the window
	// center is a cell index
	TextureManager *manager = TextureManager::Instance();
	Game *game = Game::Instance();

	// x,y coords in the grid
	int centerX = center % m_iWidth;
	int centerY = center / m_iWidth;
	unsigned int cameraHalfWidthGrid = (camera.w / 2) / m_tileset.tileWidth,
				 cameraHalfHeightGrid = (camera.h / 2) / m_tileset.tileHeight;

	// portion of the map which is visible
	int topLeftX = centerX - cameraHalfWidthGrid;
	int topLeftY = centerY - cameraHalfHeightGrid;
	int botRightX = centerX + cameraHalfWidthGrid;
	int botRightY = centerY + cameraHalfHeightGrid;

	int shiftX = topLeftX * m_tileset.tileWidth;
	int shiftY = topLeftY * m_tileset.tileHeight;
	for (int y = topLeftY; y < botRightY; ++y) {
		for (int x = topLeftX; x < botRightX; ++x) {
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
