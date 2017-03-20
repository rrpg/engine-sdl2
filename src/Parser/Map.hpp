#ifndef __MAP_PARSER__
#define __MAP_PARSER__

#include "File.hpp"
#include "../Map.hpp"

class MapParser : public FileParser {
	protected:
	Map &m_map;

	bool _parseLine(const char *line);
	bool _parseTileset(const char *line);
	void _parseMapContent(const char *line);

	public:
	MapParser(Map &map);
};

#endif
