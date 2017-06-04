#ifndef __MAP_PARSER__
#define __MAP_PARSER__

#include "Parser/File.hpp"

class Map;

class MapParser : public FileParser {
	protected:
	Map *m_map;

	bool _parseLine(const char *line);
	void _parseMapContent(const char *line);

	public:
	MapParser();
	~MapParser();
	MapParser(const MapParser &mP); // copy constructor
	MapParser & operator=(const MapParser &mP); // assignment
	void setMap(Map *map);
	bool saveMap(const char *filePath);
};

#endif
