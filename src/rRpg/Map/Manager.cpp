#include "Map/Manager.hpp"
#include "Map/Generator.hpp"
#include "Utils.hpp"
#include "Parser/Map.hpp"
#include <libgen.h>
#include <sys/stat.h>
#include <iostream>

void MapManager::_getMapPath(std::string mapName, char filePath[PATH_MAX]) {
	sprintf(
		filePath,
		"%s/maps/%s.dat",
		Utils::getDataPath().c_str(),
		mapName.c_str()
	);
}

bool MapManager::mapExists(std::string mapName) {
	char filePath[PATH_MAX];
	_getMapPath(mapName, filePath);

	struct stat buffer;
	return stat(filePath, &buffer) == 0;
}

bool MapManager::generateMap(Map &map, std::string mapFile, std::string mapName, int level) {
	char filePath[PATH_MAX];
	_getMapPath(mapFile, filePath);
	Utils::createFolder(dirname(strdup(filePath)));

	map.clear();
	map.setName(mapName);
	map.setLevel(level);
	MapParser parser = MapParser(map);

	MapGenerator generator = MapGenerator(map);
	generator.generate(CAVE, 50, 50);
	return parser.saveMap(filePath);
}

bool MapManager::loadMap(Map &map, std::string mapName) {
	char filePath[PATH_MAX];
	_getMapPath(mapName, filePath);

	map.clear();
	MapParser parser = MapParser(map);

	// load it
	E_FileParsingResult res;
	std::cout << "Loading map: " << filePath << "\n";
	res = parser.parseFile(filePath);
	if (res != OK) {
		std::cout << "error parsing map: " << res << std::endl;
		return false;
	}

	return true;
}
