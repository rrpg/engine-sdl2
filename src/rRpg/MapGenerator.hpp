#ifndef __MAP_GENERATOR__
#define __MAP_GENERATOR__

#include <string>
#include "Map.hpp"

enum E_MapType {CAVE};

class MapGenerator {
	private:
	void _generateCave(Map &map);

	public:
	MapGenerator();
	Map generate(E_MapType type, short width, short height);
};

#endif
