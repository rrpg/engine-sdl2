#include "MapEvent.hpp"
#include "rRpg.hpp"
#include <iostream>

void MapEvent::execute(rRpg *engine) {
	std::cout << "execute event with engine" << engine << "\n";
}
