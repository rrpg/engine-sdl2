#ifndef __MAP_GENERATOR__
#define __MAP_GENERATOR__

#include <string>
#include "Map.hpp"

enum E_MapType {CAVE};

class MapGenerator {
	private:
	void _generateCave(Map &map);
	void _initialiseAutomaton(Map &map);
	void _automatonStep(Map &map);
	unsigned int _getCountAliveNeighbours(Map &map, unsigned int i, unsigned int j, E_TerrainType aliveType);
	void _setStartPoint(Map &map);
	bool _findClosestWalkableCell(
		Map &map, const int x, const int y, std::vector<bool> &visited, int &xOut, int &yOut
	);

	public:
	MapGenerator();
	Map generate(E_MapType type, short width, short height);
};

#endif
