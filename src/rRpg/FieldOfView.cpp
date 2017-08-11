#include "FieldOfView.hpp"
#include <algorithm>
#include "Actor.hpp"
#include "Map.hpp"

#define PLAYER_DEPTH_OF_VIEW 12

// Those define the 8 quadrants of a 360 degrees field of vision
static int multipliers[4][8] = {
	{1, 0, 0, -1, -1, 0, 0, 1},
	{0, 1, -1, 0, 0, -1, 1, 0},
	{0, 1, 1, 0, 0, -1, -1, 0},
	{1, 0, 0, 1, -1, 0, 0, -1}
};

FieldOfView::FieldOfView(SDL_Rect visibleArea) : m_visibleArea(visibleArea) {
}

long unsigned FieldOfView::_getRelativeIndex(int x, int y) {
	int relativeX = x - m_visibleArea.x,
		relativeY = y - m_visibleArea.y;
	return (long unsigned) (relativeY * m_visibleArea.w + relativeX);
}

void FieldOfView::_setCellVisible(int x, int y) {
	m_vVisibleCells[_getRelativeIndex(x, y)] = 1;
}

bool FieldOfView::isVisible(int x, int y) {
	return m_vVisibleCells[_getRelativeIndex(x, y)] == 1;
}

void FieldOfView::calculate(Map &map, std::shared_ptr<Actor> reference) {
	m_vVisibleCells.clear();
	long unsigned sizeView = (unsigned) (m_visibleArea.w * m_visibleArea.h);
	m_vVisibleCells.assign(sizeView, 0);
	_setCellVisible(reference->getX(), reference->getY());
	for (int i = 0; i < 8; ++i) {
		_lightQuadrant(
			map,
			reference,
			1,
			1.0,
			0.0,
			multipliers[0][i],
			multipliers[1][i],
			multipliers[2][i],
			multipliers[3][i]
		);
	}
}

// Björn Bergström algorithm,
// http://www.roguebasin.com/index.php?title=FOV_using_recursive_shadowcasting
void FieldOfView::_lightQuadrant(
	Map &map,
	std::shared_ptr<Actor> reference, int row,
	double startSlope, double endSlope,
	int xx, int xy, int yx, int yy
) {
	int x = reference->getX(),
		y = reference->getY();
	if (startSlope < endSlope) {
		return;
	}
	double nextStartSlope = startSlope;
	// min(m_visibleArea.w, m_visibleArea.h, PLAYER_DEPTH_OF_VIEW)
	int depth = std::min(PLAYER_DEPTH_OF_VIEW, std::min(m_visibleArea.w, m_visibleArea.h));
	int radius2 = depth * depth;
	for (int i = row; i <= depth; i++) {
		bool blocked = false;
		for (int dx = -i, dy = -i; dx <= 0; dx++) {
			double lSlope = (dx - 0.5) / (dy + 0.5);
			double rSlope = (dx + 0.5) / (dy - 0.5);
			if (startSlope < rSlope) {
				continue;
			} else if (endSlope > lSlope) {
				break;
			}

			int sax = dx * xx + dy * xy;
			int say = dx * yx + dy * yy;
			if ((sax < 0 && (int)std::abs(sax) > x)
				|| (say < 0 && (int)std::abs(say) > y)) {
				continue;
			}
			int ax = x + sax;
			int ay = y + say;
			if (!map.areCoordinatesValid(ax, ay)) {
				continue;
			}

#ifdef __DEBUG__
			_setCellVisible(ax, ay);
			continue;
#endif

			if ((int) (dx * dx + dy * dy) < radius2) {
				_setCellVisible(ax, ay);
			}

			if (blocked) {
				if (map.isCellObstructingView(ax, ay)) {
					nextStartSlope = rSlope;
					continue;
				} else {
					blocked = false;
					startSlope = nextStartSlope;
				}
			} else if (map.isCellObstructingView(ax, ay)) {
				blocked = true;
				nextStartSlope = rSlope;
				_lightQuadrant(map, reference, i + 1, startSlope, lSlope, xx,
						xy, yx, yy);
			}
		}
		if (blocked) {
			break;
		}
	}
}

std::vector<std::pair<t_coordinates, char>> FieldOfView::getVisibleCells() {
	long unsigned sizeView = m_vVisibleCells.size();
	std::vector<std::pair<t_coordinates, char>> visible = {};
	for (long unsigned i = 0; i < sizeView; ++i) {
		t_coordinates coords = {
			(long unsigned) m_visibleArea.x + i % (long unsigned) m_visibleArea.w,
			(long unsigned) m_visibleArea.y + i / (long unsigned) m_visibleArea.w
		};
		visible.push_back(std::make_pair(coords, m_vVisibleCells[i]));
	}
	return visible;
}

SDL_Rect &FieldOfView::getVisibleArea() {
	return m_visibleArea;
}
