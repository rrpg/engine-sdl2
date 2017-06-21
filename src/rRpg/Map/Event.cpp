#include "Map/Event.hpp"
#include "rRpg.hpp"
#include <iostream>

void MapEvent::execute(rRpg *engine, const S_MapChangeEventData event) {
	engine->loadMap(event.mapName, event.mapLevel);
}
