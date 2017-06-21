#ifndef __MAP_EVENT__
#define __MAP_EVENT__

#include "types.hpp"

class rRpg;

class MapEvent {
	public:
	void execute(rRpg *engine, S_MapChangeEventData event);
};

#endif
