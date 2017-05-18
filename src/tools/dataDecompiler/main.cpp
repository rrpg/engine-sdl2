#include <iostream>
#include <unistd.h>
#include <libgen.h>
#include "Parser/Tile.hpp"
#include "ResourceManager.hpp"

std::string cleanFileInPath(std::string path);
void writeTileData(std::ofstream &fileOutStream, S_TileData tile);
bool decompileTilesFile(std::string fileIn, std::string fileOut);

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
		fileIn = cleanFileInPath(argv[2]),
		fileOut = argv[3];

	bool ret;
	if (type == "tiles") {
		ret = decompileTilesFile(fileIn, fileOut);
	}
	else {
		std::cerr << "Invalid type: " << type << "\n";
		return 2;
	}

	return ret ? 0 : 1;
}

std::string cleanFileInPath(std::string path) {
	if (path[0] == '/') {
		return path;
	}
	else {
		char cwd[1024];
		getcwd(cwd, sizeof(cwd));
		return std::string(cwd) + "/" + path;
	}
}

void writeTileData(std::ofstream &fileOutStream, S_TileData tile) {
	fileOutStream << tile.tileset << " " <<
		tile.width << " " << tile.height << " " <<
		tile.x << " " << tile.y << "\n";
}

bool decompileTilesFile(std::string fileIn, std::string fileOut) {
	ResourceManager<S_TileData> resourceManager;

	resourceManager.setResourceFile(fileIn);
	resourceManager.parseBinaryFile();
	return resourceManager.saveReadableFile(fileOut, writeTileData);
}
