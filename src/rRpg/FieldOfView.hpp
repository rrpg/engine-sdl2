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
	std::vector<t_coordinates> m_vVisibleCells = {};
	SDL_Rect m_visibleArea;

	void _lightQuadrant(
		Map &map,
		std::shared_ptr<Actor> reference, int row,
		double startSlope, double endSlope,
		int xx, int xy, int yx, int yy
	);

	public:
	FieldOfView(SDL_Rect visibleArea);
	void calculate(Map &map, std::shared_ptr<Actor> reference);
	const std::vector<t_coordinates> &getVisible();
};

#endif
