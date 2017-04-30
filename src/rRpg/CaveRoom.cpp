#include "CaveRoom.hpp"

void _floodFill(Map &map, std::vector<char> &dispatchedCells, CaveRoom::S_RoomCollection &roomCollection, CaveRoom::S_Room &currentRoom, int x, int y);

CaveRoom::S_RoomCollection CaveRoom::findRooms(Map &map) {
	CaveRoom::S_RoomCollection roomCollection;
	const size_t nbCells = map.getGrid()->size();
	int mapWidth = map.getWidth();
	std::vector<char> dispatchedCells(nbCells, 0);
	size_t nextCellToInspect = 0;

	while (nextCellToInspect < nbCells) {
		int x = (int) nextCellToInspect % mapWidth,
			y = (int) nextCellToInspect / mapWidth;
		if (dispatchedCells[nextCellToInspect] == 0 && map.isCellWalkable(x, y)) {
			CaveRoom::S_Room nextRoom;
			_floodFill(map, dispatchedCells, roomCollection, nextRoom, x, y);
			roomCollection.rooms.push_back(nextRoom);
		}

		++nextCellToInspect;
	}

	return roomCollection;
}

void _floodFill(Map &map, std::vector<char> &dispatchedCells, CaveRoom::S_RoomCollection &roomCollection, CaveRoom::S_Room &currentRoom, int x, int y) {
	size_t cellIndex = map.getTileIndex(x, y);
	if (dispatchedCells[cellIndex] == 1 || !map.isCellWalkable(x, y)) {
		return;
	}

	currentRoom.cells.push_back(cellIndex);
	dispatchedCells[cellIndex] = 1;
	roomCollection.cellRoomMapping[cellIndex] = roomCollection.rooms.size();
	if (x > 0) {
		_floodFill(map, dispatchedCells, roomCollection, currentRoom, x - 1, y);
	}
	if (x < map.getWidth() - 1) {
		_floodFill(map, dispatchedCells, roomCollection, currentRoom, x + 1, y);
	}
	if (y > 0) {
		_floodFill(map, dispatchedCells, roomCollection, currentRoom, x, y - 1);
	}
	if (y < map.getHeight() - 1) {
		_floodFill(map, dispatchedCells, roomCollection, currentRoom, x, y + 1);
	}
}
