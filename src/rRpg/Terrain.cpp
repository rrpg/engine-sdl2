#include "Terrain.hpp"

std::unordered_map<E_TerrainType, std::vector<E_TerrainTile>> Terrain::s_mTerrainMasks = createTileMasksMap();

std::unordered_map<E_TerrainType, std::vector<E_TerrainTile>> createTileMasksMap() {
	std::unordered_map<E_TerrainType, std::vector<E_TerrainTile>> map;
	map[TERRAIN_GRASS_NORMAL] = {
		TERRAIN_GRASS_NORMAL_CENTER
	};
	map[TERRAIN_SOIL_NORMAL] = {
		TERRAIN_SOIL_NORMAL_CENTER
	};
	map[TERRAIN_ROCK_NORMAL] = {
		TERRAIN_ROCK_NORMAL_CENTER
	};
	return map;
}

void Terrain::setFlags(unsigned int flags) {
	m_iFlags = flags;
}

bool Terrain::hasFlag(unsigned int flag) {
	return (m_iFlags & flag) == flag;
}

E_TerrainTile Terrain::getTerrainTile(E_TerrainType type) {
	return s_mTerrainMasks[type][0];
}
