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

E_FileParsingResult TileParser::parseBinaryFile(const char* file) {
	std::ifstream fin;
	fin.open(file);
	if (!fin.good()) {
		fin.close();
		return ERROR_OPENING_FILE;
	}

	E_FileParsingResult retValue = OK;
	char *fileDir = dirname(const_cast<char*>(file));
	strncpy(m_sFileDir, fileDir, MAX_CHAR_DIR_PATH);
	while (fin) {
		S_TileData tile;
		fin.read((char*)&tile, sizeof(tile));
		// export data
		m_file << tile.tileset << " " <<
			tile.width << " " << tile.height << " " <<
			tile.x << " " << tile.y << "\n";
	}

	fin.close();

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
