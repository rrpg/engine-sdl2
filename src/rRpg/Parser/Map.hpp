#ifndef __MAP_PARSER__
#define __MAP_PARSER__

#include "Parser/File.hpp"
#include "../Map.hpp"

class MapParser : public FileParser {
	protected:
	Map &m_map;
	int m_iTileWidth = 1;
	int m_iTileHeight = 1;

	bool _parseLine(const char *line);
	bool _parseTileset(const char *line);
	void _parseMapContent(const char *line);

	public:
	MapParser(Map &map);
};

#endif
