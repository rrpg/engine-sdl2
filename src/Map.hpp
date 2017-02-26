#ifndef __MAP__
#define __MAP__

#include "Actor.hpp"
#include <stdint.h>
#include <vector>
#include "SDL2_framework/Level.h"

enum S_MapParsingResult {
	OK,
	ERROR_OPENING_FILE,
	INVALID_LINE_FORMAT,
	INVALID_DIMENSIONS_FORMAT,
	INVALID_TILESET_DEFINITION
};

class Map {
	private:
	unsigned int m_iWidth = 0;
	unsigned int m_iHeight = 0;
	Tileset m_tileset;
	std::vector<char> m_vGrid = {};
	std::vector<Actor*> m_vActors = {};

	int _parseLine(const char *mapDir, const char *line);
	S_MapParsingResult _parseTileset(const char *mapDir, const char *line);

	public:
	S_MapParsingResult setMap(const char* mapFile);
	void addActor(Actor *actor);
};

#endif
