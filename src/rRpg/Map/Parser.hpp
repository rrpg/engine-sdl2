#ifndef __MAP_PARSER__
#define __MAP_PARSER__

#include "Parser/File.hpp"

class Map;

class MapParser : public FileParser {
	protected:
	Map &m_map;

	bool _parseLine(const char *line);
	void _parseMapContent(const char *line);

	public:
	MapParser(Map &map);
	~MapParser();
	bool saveMap(const char *filePath);
};

#endif
