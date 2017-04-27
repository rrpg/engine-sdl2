#ifndef __CAVE_ROOM__
#define __CAVE_ROOM__

#include "Map.hpp"

namespace CaveRoom {

typedef struct {
	std::vector<size_t> cells = {};
} S_Room;

typedef struct {
	std::vector<S_Room> rooms = {};
	std::unordered_map<size_t, size_t> cellRoomMapping = {};
} S_RoomCollection;

S_RoomCollection findRooms(Map &map);

}

#endif
