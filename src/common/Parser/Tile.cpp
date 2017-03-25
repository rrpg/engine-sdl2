#include "Tile.hpp"
#include "Parser/Resource.hpp"
#include <string.h>
#include <iostream>
#include <libgen.h>
#include <fstream>

TileParser::TileParser(const char *pathFileOut) {
	m_file = fopen(pathFileOut, "wb");
}

TileParser::TileParser(const TileParser &r) :
	m_file(r.m_file)
{
}

TileParser & TileParser::operator=(const TileParser &r) {
	// check for "self assignment" and do nothing in that case
	if (this == &r) {
		return *this;
	}

	m_file = r.m_file;
	return *this;
}

TileParser::~TileParser() {
	fclose (m_file);
}

bool TileParser::_parseLine(const char *line) {
	bool retValue = true;
	char tileset[ResourceParser::MAX_CHAR_RESOURCE_NAME];
	unsigned int tileWidth, tileHeight, tilesetX, tilesetY;
	int result = sscanf(
		line,
		"%s %u %u %u %u\n",
		tileset, &tileWidth, &tileHeight, &tilesetX, &tilesetY);
	if (result != 5) {
		retValue = false;
	}
	else {
		int sizeTilesetName = (int) strlen(tileset);
		fputc(sizeTilesetName, m_file);
		fputs(tileset, m_file);
		for (int pad = sizeTilesetName; pad < MAX_LENGTH_TILESET_NAME; ++pad) {
			fputc('0', m_file);
		}
		fputc(tileWidth, m_file);
		fputc(tileHeight, m_file);
		fputc(tilesetX, m_file);
		fputc(tilesetY, m_file);
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
	char tileData[MAX_BYTES_PER_CHUNK];
	while (fin.read(tileData, MAX_BYTES_PER_CHUNK)) {
		// organise data
		S_TileData tile = _extractTile(tileData);

		// export data
		fputs(tile.tileset, m_file);
		fputc(' ', m_file);
		fputs(std::to_string(tile.width).c_str(), m_file);
		fputc(' ', m_file);
		fputs(std::to_string(tile.height).c_str(), m_file);
		fputc(' ', m_file);
		fputs(std::to_string(tile.x).c_str(), m_file);
		fputc(' ', m_file);
		fputs(std::to_string(tile.y).c_str(), m_file);
		fputc('\n', m_file);
	}

	fin.close();

	return retValue;
}

int TileParser::getTileInfo(S_TileData &tileInfo, FILE *tileFile, int tileIndex) {
	int ret = fseek(tileFile, tileIndex * MAX_BYTES_PER_CHUNK, SEEK_SET);
	if (ret == 0) {
		char tileData[MAX_BYTES_PER_CHUNK];
		ret = 0;
		if (fread(tileData, 1, MAX_BYTES_PER_CHUNK, tileFile) == MAX_BYTES_PER_CHUNK) {
			tileInfo = _extractTile(tileData);
			std::cout << "Tileset: " << tileInfo.tileset << "\n";
			std::cout << "Width: " << (int) tileInfo.width << "\n";
			ret = 1;
		}
	}

	return ret;
}

S_TileData TileParser::_extractTile(char tileData[MAX_BYTES_PER_CHUNK]) {
	S_TileData tile;
	for (int c = 0; c < tileData[0]; ++c) {
		tile.tileset[c] = tileData[c + 1];
	}
	tile.tileset[(int) tileData[0]] = '\0';
	tile.width = tileData[MAX_LENGTH_TILESET_NAME + 1];
	tile.height = tileData[MAX_LENGTH_TILESET_NAME + 2];
	tile.x = tileData[MAX_LENGTH_TILESET_NAME + 3];
	tile.y = tileData[MAX_LENGTH_TILESET_NAME + 4];
	return tile;
}
