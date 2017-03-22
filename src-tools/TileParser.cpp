#include "TileParser.hpp"
#include "Parser/Resource.hpp"
#include <string.h>
#include <iostream>
#include <libgen.h>
#include <fstream>

// lenTileset + tileset + width + height + x + y
// 1 + 255 + 1 + 1 + 1 + 1
const int MAX_BYTES_PER_CHUNK = 260;

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
		int sizeTilesetName = strlen(tileset);
		fputc(sizeTilesetName, m_file);
		fputs(tileset, m_file);
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
	while (!fin.eof()) {
		char buf;
		// tileset
		char sizeTileset = 0;
		fin.read(&sizeTileset, 1);
		if (fin.eof()) {
			break;
		}
		for (char c = 0; c < sizeTileset; ++c) {
			fin.read(&buf, 1);
			fputc(buf, m_file);
		}

		// width, height, x, y
		for (char num = 0; num < 4; ++num) {
			fputc(' ', m_file);
			fin.read(&buf, 1);
			fputs(std::to_string(buf).c_str(), m_file);
		}
		fputc('\n', m_file);
	}

	fin.close();

	return retValue;
}
