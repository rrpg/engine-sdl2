#include "FieldOfView.hpp"
#include "Actor.hpp"
#include "Map.hpp"

void FieldOfView::calculate(Map &map, std::shared_ptr<Actor> reference) {
	m_vVisibleCells.clear();
	for (int x = reference->getX() - 8; x < reference->getX() + 8; ++x) {
		for (int y = reference->getY() - 8; y < reference->getY() + 8; ++y) {
			if (map.areCoordinatesValid(x, y)) {
				m_vVisibleCells.push_back({x, y});
			}
		}
	}
}

const std::vector<t_coordinates> &FieldOfView::getVisible() {
	return m_vVisibleCells;
}
