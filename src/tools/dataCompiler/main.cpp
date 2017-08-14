#include <iostream>
#include <unistd.h>
#include <libgen.h>
#include "types.hpp"
#include "ResourceManager.hpp"

std::string cleanFileInPath(std::string path);
bool readTileFileLine(char line[MAX_CHARS_PER_LINE], S_TileData &data);
bool readTilesetFileLine(char line[MAX_CHARS_PER_LINE], S_TilesetMapping &data);
bool readRaceLine(char line[MAX_CHARS_PER_LINE], S_ActorRaceData &data);
bool readObjectLine(char line[MAX_CHARS_PER_LINE], S_ObjectData &data);

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
	else if (type == "tilesets") {
		ResourceManager<S_TilesetMapping> resourceManager;
		bool res = resourceManager.compileFile(fileIn, fileOut, readTilesetFileLine);
		if (!res) {
			return 1;
		}
	}
	else if (type == "races") {
		ResourceManager<S_ActorRaceData> resourceManager;
		bool res = resourceManager.compileFile(fileIn, fileOut, readRaceLine);
		if (!res) {
			return 1;
		}
	}
	else if (type == "objects") {
		ResourceManager<S_ObjectData> resourceManager;
		bool res = resourceManager.compileFile(fileIn, fileOut, readObjectLine);
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
		char* res = getcwd(cwd, sizeof(cwd));
		if (!res) {
			return "./" + path;
		}

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

bool readTilesetFileLine(char line[MAX_CHARS_PER_LINE], S_TilesetMapping &data) {
	int result = sscanf(
		line,
		"%s %s\n",
		data.tileset, data.filePath);
	return result == 2;
}

bool readRaceLine(char line[MAX_CHARS_PER_LINE], S_ActorRaceData &data) {
	int result = sscanf(
		line,
		"%s %d %d %d %d %d %d\n",
		data.tileset, &data.timePerFrame, &data.spriteX, &data.spriteY,
		&data.level1HP, &data.level1Defence, &data.level1Attack
	);
	if (result != 7) {
		return false;
	}

	return true;
}

bool readObjectLine(char line[MAX_CHARS_PER_LINE], S_ObjectData &data) {
	int result = sscanf(
		line,
		"%s %d %d %u\n",
		data.tileset, &data.spriteX, &data.spriteY, &data.flags);
	return result == 4;
}
