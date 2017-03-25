#include "Terrain.hpp"

void Terrain::setTile(S_TileData tileData) {
	m_sTileData = tileData;
}

S_TileData Terrain::getTile() {
	return m_sTileData;
}

void Terrain::setFlags(unsigned int flags) {
	m_iFlags = flags;
}

bool Terrain::hasFlag(unsigned int flag) {
	return (m_iFlags & flag) == flag;
}
