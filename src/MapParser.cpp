#include "MapParser.hpp"
#include "SDL2_framework/TextureManager.h"
#include "SDL2_framework/Game.h"
#include <string.h>

const int MAX_CHAR_TILESET_NAME = 100;
const int MAX_CHAR_TILESET_FILE = 100;

MapParser::MapParser(Map* map) : m_map(map) {
}

MapParser::MapParser(const MapParser &r) : m_map(r.m_map) {
}

MapParser & MapParser::operator=(const MapParser &r) {
	// check for "self assignment" and do nothing in that case
	if (this == &r) {
		return *this;
	}

	m_map = r.m_map;
	return *this;
}

MapParser::~MapParser() {

}

bool MapParser::_parseLine(const char *mapDir, const char *line) {
	bool retValue = true;
	int sscanfResult;
	char type;

	if (strlen(line) < 3) {
		return false;
	}

	type = *line;
	line += 2;
	switch (type) {
		case 'd':
			unsigned int w, h;
			sscanfResult = sscanf(line, "%u %u\n", &w, &h);
			if (sscanfResult != 2) {
				retValue = false;
			}
			m_map->setDimensions(w, h);
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
				retValue = false;
			}
			m_map->setStartPoint((float) x, (float) y);
			break;
		default:
			break;
	}

	return retValue;
}

void MapParser::_parseMapContent(const char *line) {
	while (*line != '\n' && *line != '\0') {
		uint32_t cellInfo = *line - '0';
		bool canSpawnEnemy = cellInfo & 0x1;
		uint8_t cellTile = (cellInfo >> 0x1) & 255;
		// the an enemy can spawn on the cell
		if (canSpawnEnemy) {
			m_map->addEnemySpawnableCell((int) m_map->getGrid()->size());
		}

		m_map->getGrid()->push_back(cellTile);
		++line;
	}
}

bool MapParser::_parseTileset(const char *mapDir, const char *line) {
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
		return false;
	}

	std::string textureFile = std::string(mapDir) + "/" + tilesetPath;

	// first add the tileset to texture manager
	TextureManager::Instance()->load(
		textureFile,
		tilesetName,
		Game::Instance()->getRenderer()
	);

	tileset.tileWidth = tileSize;
	tileset.tileHeight = tileSize;
	tileset.width = tileSize * tilesetWidth;
	tileset.name = tilesetName;
	tileset.numColumns = tilesetWidth;
	m_map->setTileset(tileset);
	return true;
}
