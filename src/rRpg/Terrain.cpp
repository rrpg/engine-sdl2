#include "Terrain.hpp"

void Terrain::setTile(S_TileData tileData) {
	m_sTileData = tileData;
	m_bHasTileData = true;
}

S_TileData Terrain::getTile() {
	return m_sTileData;
}

bool Terrain::hasTile() {
	return m_bHasTileData;
}

void Terrain::setFlags(unsigned int flags) {
	m_iFlags = flags;
}

bool Terrain::hasFlag(unsigned int flag) {
	return (m_iFlags & flag) == flag;
}
