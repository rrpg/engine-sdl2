#include "Map.hpp"

#include <string.h>
#include <fstream>
#include <libgen.h>
#include "SDL2_framework/TextureManager.h"
#include "SDL2_framework/Game.h"

const int MAX_CHARS_PER_LINE = 1024;
const int MAX_CHAR_TILESET_NAME = 100;
const int MAX_CHAR_TILESET_FILE = 100;

S_MapParsingResult Map::setMap(const char* mapFile) {
	std::ifstream fin;
	fin.open(mapFile);
	if (!fin.good()) {
		fin.close();
		return ERROR_OPENING_FILE;
	}


	char *mapDir = dirname(const_cast<char*>(mapFile));
	while (!fin.eof()) {
		char buf[MAX_CHARS_PER_LINE];
		// @check too long lines
		fin.getline(buf, MAX_CHARS_PER_LINE);

		if (buf[0] == '\0' || buf[0] == '#') {
			continue;
		}

		_parseLine(mapDir, buf);
	}

	fin.close();
	return OK;
}

int Map::_parseLine(const char *mapDir, const char *line) {
	int retValue = OK;
	char type;

	if (strlen(line) < 3) {
		return INVALID_LINE_FORMAT;
	}

	type = *line;
	line += 2;
	switch (type) {
		case 'd':
			retValue = sscanf(line, "%u %u\n", &m_iWidth, &m_iHeight);
			if (retValue != 2) {
				retValue = INVALID_DIMENSIONS_FORMAT;
			}
			break;
		case 'c':
			while (*line != '\n' && *line != '\0') {
				m_vGrid.push_back(*line);
				++line;
			}
			break;
		case 't':
			retValue = _parseTileset(mapDir, line);
			break;
		default:
			break;
	}

	return retValue;
}

S_MapParsingResult Map::_parseTileset(const char *mapDir, const char *line) {
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
