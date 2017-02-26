#ifndef __MAP__
#define __MAP__

#include "Actor.hpp"
#include <stdint.h>
#include <vector>
#include "SDL2_framework/Level.h"
#include <SDL2/SDL.h>

enum E_MapParsingResult {
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
	std::vector<int> m_vGrid = {};
	std::vector<Actor*> m_vActors = {};

	E_MapParsingResult _parseLine(const char *mapDir, const char *line);
	E_MapParsingResult _parseTileset(const char *mapDir, const char *line);
	void _parseMapContent(const char *line);

	public:
	E_MapParsingResult setMap(const char* mapFile);
	void addActor(Actor *actor);
	void render(SDL_Rect camera, int center);
};

#endif
