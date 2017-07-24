#ifndef __FIELD_OF_VIEW__
#define __FIELD_OF_VIEW__

#include "types.hpp"
#include <vector>
#include <memory>
#include <SDL2/SDL.h>

class Actor;
class Map;

class FieldOfView {
	private:
	std::vector<int> m_vVisibleCells = {};
	SDL_Rect m_visibleArea;

	void _lightQuadrant(
		Map &map,
		std::shared_ptr<Actor> reference, int row,
		double startSlope, double endSlope,
		int xx, int xy, int yx, int yy
	);
	void _setCellVisible(int x, int y);

	public:
	FieldOfView(SDL_Rect visibleArea);
	void calculate(Map &map, std::shared_ptr<Actor> reference);
	std::vector<t_coordinates> getVisible();
};

#endif
