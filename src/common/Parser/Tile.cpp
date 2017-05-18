#include "Tile.hpp"
#include "Parser/Resource.hpp"
#include <string.h>
#include <libgen.h>

TileParser::TileParser(const char *pathFileOut) : m_file(std::ofstream(pathFileOut, std::ios::binary)) {
}

TileParser::~TileParser() {
	m_file.close();
}

bool TileParser::_parseLine(const char *line) {
	bool retValue = true;
	S_TileData data;
	int result = sscanf(
		line,
		"%s %d %d %d %d\n",
		data.tileset, &data.width, &data.height, &data.x, &data.y);
	if (result != 5) {
		retValue = false;
	}
	else {
		m_file.write((char*)&data, sizeof(data));
	}

	return retValue;
}

int TileParser::getTileInfo(S_TileData &tileInfo, FILE *tileFile, int tileIndex) {
	int ret = fseek(tileFile, tileIndex * MAX_BYTES_PER_CHUNK, SEEK_SET);
	if (ret == 0) {
		ret = 0;
		if (fread((char*)&tileInfo, 1, MAX_BYTES_PER_CHUNK, tileFile) == MAX_BYTES_PER_CHUNK) {
			ret = 1;
		}
	}

	return ret;
}
