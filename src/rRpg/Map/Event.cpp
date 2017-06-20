#include "Map/Event.hpp"
#include "rRpg.hpp"
#include <iostream>

void MapEvent::execute(rRpg *engine) {
	engine->loadMap(
		engine->getMap().getName(),
		engine->getMap().getLevel() + 1
	);
}
