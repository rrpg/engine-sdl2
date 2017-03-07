#ifndef __MAP_PARSER__
#define __MAP_PARSER__

#include "FileParser.hpp"
#include "Map.hpp"

class MapParser : public FileParser {
	protected:
	Map* m_map;

	bool _parseLine(const char *fileDir, const char *line);
	bool _parseTileset(const char *mapDir, const char *line);
	void _parseMapContent(const char *line);

	public:
	MapParser(Map* map);
	MapParser(const MapParser &L); // copy constructor
	MapParser & operator=(const MapParser &L); // assignment
	~MapParser();
};

#endif
