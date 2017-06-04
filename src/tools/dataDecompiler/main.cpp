#include <iostream>
#include <unistd.h>
#include <libgen.h>
#include "types.hpp"
#include "ResourceManager.hpp"

std::string cleanFileInPath(std::string path);
void writeTileData(std::ofstream &fileOutStream, S_TileData tile);
void writeTilesetMapping(std::ofstream &fileOutStream, S_TilesetMapping tile);
void writeActorRace(std::ofstream &fileOutStream, S_ActorRaceData race);
void writeObject(std::ofstream &fileOutStream, S_ObjectData object);
template <typename T>
bool decompileFile(
	ResourceManager<T> *resourceManager,
	void (callback)(std::ofstream&, T),
	std::string fileIn,
	std::string fileOut
);

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
		ret = decompileFile(new ResourceManager<S_TileData>(), writeTileData, fileIn, fileOut);
	}
	else if (type == "tilesets") {
		ret = decompileFile(new ResourceManager<S_TilesetMapping>(), writeTilesetMapping, fileIn, fileOut);
	}
	else if (type == "races") {
		ret = decompileFile(new ResourceManager<S_ActorRaceData>(), writeActorRace, fileIn, fileOut);
	}
	else if (type == "objects") {
		ret = decompileFile(new ResourceManager<S_ObjectData>(), writeObject, fileIn, fileOut);
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
		char* res = getcwd(cwd, sizeof(cwd));
		if (!res) {
			return "./" + path;
		}

		return std::string(cwd) + "/" + path;
	}
}

void writeTileData(std::ofstream &fileOutStream, S_TileData tile) {
	fileOutStream << tile.tileset << " " <<
		tile.width << " " << tile.height << " " <<
		tile.x << " " << tile.y << "\n";
}

void writeTilesetMapping(std::ofstream &fileOutStream, S_TilesetMapping tile) {
	fileOutStream << tile.tileset << " " << tile.filePath << "\n";
}

void writeActorRace(std::ofstream &fileOutStream, S_ActorRaceData race) {
	fileOutStream << race.tileset << " " << race.timePerFrame << " "
		<< race.spriteX << " " << race.spriteY << " "
		<< race.level1HP << " "
		<< race.level1Defence << " " << race.level1Attack << "\n";
}

void writeObject(std::ofstream &fileOutStream, S_ObjectData object) {
	fileOutStream << object.tileset << " "
		<< object.spriteX << " " << object.spriteY << "\n";
}

template <typename T>
bool decompileFile(
	ResourceManager<T> *resourceManager,
	void (callback)(std::ofstream&, T),
	std::string fileIn,
	std::string fileOut
) {
	resourceManager->setResourceFile(fileIn);
	resourceManager->parseBinaryFile();
	bool ret = resourceManager->saveReadableFile(fileOut, callback);
	delete resourceManager;
	return ret;
}
