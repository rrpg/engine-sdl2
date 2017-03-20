#include "FileParser.hpp"
#include <fstream>
#include <libgen.h>
#include <string.h>

const int MAX_CHARS_PER_LINE = 1024;

E_FileParsingResult FileParser::parseFile(const char* file) {
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
		char buf[MAX_CHARS_PER_LINE];
		// @check too long lines
		fin.getline(buf, MAX_CHARS_PER_LINE);

		if (buf[0] == '\0' || buf[0] == '#') {
			continue;
		}

		if (!_parseLine(buf)) {
			retValue = ERROR_LINE_PARSING;
			break;
		}
	}

	fin.close();

	return retValue;
}
