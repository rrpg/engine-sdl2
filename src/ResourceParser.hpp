#ifndef __RESOURCE_PARSER__
#define __RESOURCE_PARSER__

#include "FileParser.hpp"

class ResourceParser : public FileParser {
	protected:
	bool _parseLine(const char *line);

	public:
	const static int MAX_CHAR_RESOURCE_NAME = 32;
	const static int MAX_CHAR_RESOURCE_PATH = 255;

};

#endif
