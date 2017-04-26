#ifndef __CAVE_ROOM__
#define __CAVE_ROOM__

#include "Map.hpp"

namespace CaveRoom {

typedef struct {
	std::vector<size_t> cells = {};
} S_Room;

std::vector<S_Room> findRooms(Map &map);

}

#endif
