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

	public:
	void calculate(Map &map, std::shared_ptr<Actor> reference);
	const std::vector<t_coordinates> &getVisible();
};

#endif
