#ifndef __FIELD_OF_VIEW__
#define __FIELD_OF_VIEW__

#include "types.hpp"
#include <vector>
#include <memory>

class Actor;
class Map;

class FieldOfView {
	private:
	std::vector<t_coordinates> m_vVisibleCells = {};

	void _lightQuadrant(
		Map &map,
		std::shared_ptr<Actor> reference, int row,
		double startSlope, double endSlope,
		int xx, int xy, int yx, int yy
	);

	public:
	void calculate(Map &map, std::shared_ptr<Actor> reference);
	const std::vector<t_coordinates> &getVisible();
};

#endif
