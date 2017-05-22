#include <iostream>
#include <unistd.h>
#include <libgen.h>
#include "types.hpp"
#include "ResourceManager.hpp"

std::string cleanFileInPath(std::string path);
bool readTileFileLine(char line[MAX_CHARS_PER_LINE], S_TileData &data);

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

	if (type == "tiles") {
		ResourceManager<S_TileData> resourceManager;
		bool res = resourceManager.compileFile(fileIn, fileOut, readTileFileLine);
		if (!res) {
			return 1;
		}
	}
	else {
		std::cerr << "Invalid type: " << type << "\n";
		return 2;
	}
	return 0;
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

bool readTileFileLine(char line[MAX_CHARS_PER_LINE], S_TileData &data) {
	int result = sscanf(
		line,
		"%s %d %d %d %d\n",
		data.tileset, &data.width, &data.height, &data.x, &data.y);
	return result == 5;
}
