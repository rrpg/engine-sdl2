#include "Terrain.hpp"

void Terrain::setFlags(unsigned int flags) {
	m_iFlags = flags;
}

bool Terrain::hasFlag(unsigned int flag) {
	return (m_iFlags & flag) == flag;
}
