#include "Map.hpp"

#include <string.h>
#include <fstream>

const int MAX_CHARS_PER_LINE = 1024;

S_MapParsingResult Map::setMap(const char* mapFile) {
	std::ifstream fin;
	fin.open(mapFile);
	if (!fin.good()) {
		fin.close();
		return ERROR_OPENING_FILE;
	}

	while (!fin.eof()) {
		char buf[MAX_CHARS_PER_LINE];
		// @check too long lines
		fin.getline(buf, MAX_CHARS_PER_LINE);

		if (buf[0] == '\0' || buf[0] == '#') {
			continue;
		}

		_parseLine(buf);
	}

	fin.close();
	return OK;
}

int Map::_parseLine(const char *line) {
	int retValue = OK;

	if (strlen(line) < 3) {
		return INVALID_LINE_FORMAT;
	}

	char type = *line;
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
		default:
			break;
	}

	return retValue;
}

void Map::addActor(Actor *actor) {
	m_vActors.push_back(actor);
}
