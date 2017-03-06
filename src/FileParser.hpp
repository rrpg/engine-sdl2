#ifndef __FILE_PARSER__
#define __FILE_PARSER__

enum E_FileParsingResult {
	OK,
	ERROR_OPENING_FILE,
	ERROR_LINE_PARSING
};

class FileParser {
	protected:
	virtual bool _parseLine(const char *fileDir, const char *line) = 0;

	public:
	E_FileParsingResult parseFile(const char* file);
};

#endif
