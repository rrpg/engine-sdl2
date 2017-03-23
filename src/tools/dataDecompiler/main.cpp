#include <iostream>
#include <libgen.h>
#include "Parser/Tile.hpp"

int main(int argc, char* argv[]) {
	// expects the following arguments:
	// dataType (tiles),
	// dataFileIn (path to the humanly readable file),
	// dataFileOut (path to the compiled file)

	if (argc != 4) {
		std::cerr << "Usage: " << argv[0] << " dataType dataFileIn dataFileOut\n";
		return 1;
	}

	std::string type = argv[1],
		fileIn = argv[2],
		fileOut = argv[3];

	if (type == "tiles") {
		TileParser parser = TileParser(fileOut.c_str());
		E_FileParsingResult result = parser.parseBinaryFile(fileIn.c_str());
		if (result != OK) {
			std::cerr << "Error while parsing file " << fileIn << ": ";
			std::cerr << result << "\n";
			return 3;
		}
	}
	else {
		std::cerr << "Invalid type: " << type << "\n";
		return 2;
	}
	return 0;
}
