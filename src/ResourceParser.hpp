#ifndef __RESOURCE_PARSER__
#define __RESOURCE_PARSER__

#include "FileParser.hpp"

class ResourceParser : public FileParser {
	protected:
	bool _parseLine(const char *line);
};

#endif
