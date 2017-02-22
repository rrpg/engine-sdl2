#include "Map.hpp"

void Map::addActor(Actor *actor) {
	m_vActors.push_back(actor);
}

void Map::clean() {
	if (m_aGrid != NULL) {
		free(m_aGrid);
		m_aGrid = NULL;
	}
}
