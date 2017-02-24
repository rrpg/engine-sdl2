#ifndef __MAP__
#define __MAP__

#include "Actor.hpp"
#include <stdint.h>
#include <vector>

enum S_MapParsingResult {
	OK,
	ERROR_OPENING_FILE,
	INVALID_LINE_FORMAT,
	INVALID_DIMENSIONS_FORMAT
};

class Map {
	private:
	unsigned int m_iWidth = 0;
	unsigned int m_iHeight = 0;
	std::vector<char> m_vGrid = {};
	std::vector<Actor*> m_vActors = {};

	int _parseLine(const char *line);

	public:
	S_MapParsingResult setMap(const char* mapFile);
	void addActor(Actor *actor);
};

#endif
