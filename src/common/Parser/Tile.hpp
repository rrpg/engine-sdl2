#ifndef __TILE_PARSER__
#define __TILE_PARSER__

#include "Parser/File.hpp"
#include <stdio.h>

#define MAX_LENGTH_TILESET_NAME 32

struct S_TileData {
	char tileset[MAX_LENGTH_TILESET_NAME];
	char width;
	char height;
	char x;
	char y;
};

class TileParser : public FileParser {
	protected:
	bool _parseLine(const char *line);
	bool _parseBinaryLine(const char *chunk);
	FILE * m_file = 0;

	public:
	TileParser(const char *pathFileOut);
	TileParser(const TileParser &L); // copy constructor
	TileParser & operator=(const TileParser &L); // assignment
	~TileParser();
	E_FileParsingResult parseBinaryFile(const char* file);
};

#endif
