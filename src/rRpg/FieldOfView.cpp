#include "FieldOfView.hpp"
#include "Actor.hpp"
#include "Map.hpp"

#define PLAYER_DEPTH_OF_VIEW 12

void FieldOfView::calculate(Map &map, std::shared_ptr<Actor> reference) {
	m_vVisibleCells.clear();
	for (int x = reference->getX() - PLAYER_DEPTH_OF_VIEW; x < reference->getX() + PLAYER_DEPTH_OF_VIEW; ++x) {
		for (int y = reference->getY() - PLAYER_DEPTH_OF_VIEW; y < reference->getY() + PLAYER_DEPTH_OF_VIEW; ++y) {
			if (map.areCoordinatesValid(x, y)) {
				m_vVisibleCells.push_back({x, y});
			}
		}
	}
}

const std::vector<t_coordinates> &FieldOfView::getVisible() {
	return m_vVisibleCells;
}
