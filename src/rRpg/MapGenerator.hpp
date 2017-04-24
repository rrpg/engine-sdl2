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
		Map &map,
		const unsigned int x,
		const unsigned int y,
		std::vector<bool> &visited,
		unsigned int &xOut,
		unsigned int &yOut
	);
	void _dispatchEnemies(Map &map, const unsigned int nbMaxEnemies);

	public:
	MapGenerator();
	Map generate(E_MapType type, unsigned short width, unsigned short height);
};

#endif
