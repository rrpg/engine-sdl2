#include "FieldOfView.hpp"
#include "Actor.hpp"
#include "Map.hpp"

#define PLAYER_DEPTH_OF_VIEW 12
#define SQ_PLAYER_DEPTH_OF_VIEW 144

// Those define the 8 quadrants of a 360 degrees field of vision
static int multipliers[4][8] = {
	{1, 0, 0, -1, -1, 0, 0, 1},
	{0, 1, -1, 0, 0, -1, 1, 0},
	{0, 1, 1, 0, 0, -1, -1, 0},
	{1, 0, 0, 1, -1, 0, 0, -1}
};

void FieldOfView::calculate(Map &map, std::shared_ptr<Actor> reference) {
	m_vVisibleCells.clear();
	m_vVisibleCells.push_back({reference->getX(), reference->getY()});
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
    for (int i = row; i <= PLAYER_DEPTH_OF_VIEW; i++) {
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

            int radius2 = SQ_PLAYER_DEPTH_OF_VIEW;
            if ((int) (dx * dx + dy * dy) < radius2) {
				m_vVisibleCells.push_back({ax, ay});
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

const std::vector<t_coordinates> &FieldOfView::getVisible() {
	return m_vVisibleCells;
}
