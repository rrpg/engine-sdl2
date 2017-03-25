#ifndef __TILE_PARSER__
#define __TILE_PARSER__

#include "Parser/File.hpp"
#include <stdio.h>

#define MAX_LENGTH_TILESET_NAME 32
// lenTileset + tileset + width + height + x + y
// 1 + MAX_LENGTH_TILESET_NAME + 1 + 1 + 1 + 1
#define MAX_BYTES_PER_CHUNK 37

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
	static S_TileData _extractTile(char tileData[MAX_BYTES_PER_CHUNK]);
	FILE * m_file = 0;

	public:
	TileParser(const char *pathFileOut);
	TileParser(const TileParser &L); // copy constructor
	TileParser & operator=(const TileParser &L); // assignment
	~TileParser();
	E_FileParsingResult parseBinaryFile(const char* file);
	static int getTileInfo(S_TileData &tileInfo, FILE *tileFile, int tileIndex);
};

#endif
