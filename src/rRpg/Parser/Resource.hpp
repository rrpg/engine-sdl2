#ifndef __RESOURCE_PARSER__
#define __RESOURCE_PARSER__

#include "File.hpp"

class ResourceParser : public FileParser {
	protected:
	bool _parseLine(const char *line);

	public:
	const static unsigned char MAX_CHAR_RESOURCE_NAME = 32;
	const static unsigned char MAX_CHAR_RESOURCE_PATH = 255;

};

#endif
