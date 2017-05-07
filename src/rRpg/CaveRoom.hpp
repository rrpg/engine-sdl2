#ifndef __CAVE_ROOM__
#define __CAVE_ROOM__

#include "Map.hpp"

namespace CaveRoom {

struct S_Room {
	S_Room() : cells({}) {}
	std::vector<size_t> cells = {};
};

struct S_RoomCollection {
	S_RoomCollection() : cellRoomMapping({}) {}
	std::vector<S_Room> rooms = {};
	std::unordered_map<size_t, size_t> cellRoomMapping;
};

S_RoomCollection findRooms(Map &map);

}

#endif
