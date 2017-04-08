#include "MapGenerator.hpp"
#include "Terrain.hpp"

MapGenerator::MapGenerator() {
}

Map MapGenerator::generate(E_MapType type, short width, short height) {
	Map map;
	map.setDimensions(width, height);
	map.setDisplayTileDimensions(16, 16);
	map.setStartPoint(
		(float) (rand() % width),
		(float) (rand() % height)
	);


	if (type == CAVE) {
		_generateCave(map);
	}

	return map;
}

void MapGenerator::_generateCave(Map &map) {
	map.initializeGrid(TERRAIN_ROCK_NORMAL_CENTER);
	int startPointX = (int) map.getStartPoint().getX(),
		startPointY = (int) map.getStartPoint().getY();
	map.setTile(startPointX, startPointY, TERRAIN_SOIL_NORMAL_CENTER);
	map.setTile(startPointX + 1, startPointY, TERRAIN_SOIL_NORMAL_CENTER);
	map.setTile(startPointX - 1, startPointY, TERRAIN_SOIL_NORMAL_CENTER);
	map.setTile(startPointX, startPointY + 1, TERRAIN_SOIL_NORMAL_CENTER);
	map.setTile(startPointX, startPointY - 1, TERRAIN_SOIL_NORMAL_CENTER);
}
