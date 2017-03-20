#ifndef __FILE_PARSER__
#define __FILE_PARSER__

enum E_FileParsingResult {
	OK,
	ERROR_OPENING_FILE,
	ERROR_LINE_PARSING
};
const int MAX_CHAR_DIR_PATH = 255;

class FileParser {
	protected:
	char m_sFileDir[MAX_CHAR_DIR_PATH];

	virtual bool _parseLine(const char *line) = 0;

	public:
	virtual ~FileParser() {}
	E_FileParsingResult parseFile(const char* file);
};

#endif
