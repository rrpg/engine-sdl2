#include "MapManager.hpp"
#include "MapGenerator.hpp"
#include "Utils.hpp"
#include "Parser/Map.hpp"
#include <libgen.h>
#include <sys/stat.h>
#include <iostream>

MapManager::MapManager() :
	m_map(Map())
{
}

bool MapManager::loadMap(std::string mapName, int level) {
	MapParser parser = MapParser();
	char filePath[512];
	sprintf(
		filePath,
		"%s/maps/%s-%d.dat",
		Utils::getDataPath().c_str(),
		mapName.c_str(),
		level
	);

	m_map.clear();
	parser.setMap(&m_map);
	// generate the map if it does not exist
	struct stat buffer;
	if (stat(filePath, &buffer) != 0) {
		Utils::createFolder(dirname(strdup(filePath)));
		MapGenerator generator = MapGenerator(m_map);
		generator.generate(CAVE, 50, 50);
		parser.saveMap(filePath);
	}
	else {
		// load it
		E_FileParsingResult res;
		std::cout << "Loading map: " << filePath << "\n";
		res = parser.parseFile(filePath);
		if (res != OK) {
			std::cout << "error parsing map: " << res << std::endl;
			return false;
		}
	}

	m_map.setName(mapName);
	m_map.setLevel(level);

	return true;
}

Map &MapManager::getMap() {
	return m_map;
}
