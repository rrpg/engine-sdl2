#ifndef __TERRAIN__
#define __TERRAIN__

#include "types.hpp"
#include <unordered_map>
#include <vector>
#include "dataTypes.hpp"

MyUnorderedMap<E_TerrainType, std::vector<E_TerrainTile>> createTileMasksMap();

class Terrain {
	private:
	unsigned int m_iFlags = 0;
	static MyUnorderedMap<E_TerrainType, std::vector<E_TerrainTile>> s_mTerrainMasks;

	public:
	static const int TERRAIN_FLAG_WALKABLE = 0x1;
	static const int TERRAIN_FLAG_OBSTRUCTING_VIEW = 0x2;
	static const int TERRAIN_FLAG_BASE = 0x4;

	static E_TerrainTile getTerrainTile(E_TerrainType type, int index);
	void setFlags(unsigned int flags);
	bool hasFlag(unsigned int flag);
};

#endif
