#ifndef __MAP_GENERATOR__
#define __MAP_GENERATOR__

#include <string>
#include <vector>
#include "Map.hpp"
#include "CaveRoom.hpp"

class MapGenerator {
	private:
	void _generateCave(Map &map);
	void _initialiseAutomaton(Map &map);
	void _automatonStep(Map &map);
	void _joinRooms(Map &map);
	void _cleanRooms(Map &map);
	std::vector<CaveRoom::S_Room>::iterator _largestRoom(std::vector<CaveRoom::S_Room> &rooms);
	size_t _digBetweenRooms(CaveRoom::S_RoomCollection &roomCollection, Map &map, size_t cell1Index, size_t cell2Index);
	int _getCountAliveNeighbours(Map &map, int i, int j, E_TerrainType aliveType);
	void _setStartPoint(Map &map);
	std::vector<t_coordinates> _findWalkableNeighbours(Map &map, const int x, const int y);
	bool _findClosestWalkableCell(
		Map &map,
		const int x,
		const int y,
		std::vector<bool> &visited,
		int &xOut,
		int &yOut
	);
	void _dispatchEnemies(Map &map, const int nbMaxEnemies);
	void _addStairToNextLevel(Map &map);

	public:
	MapGenerator();
	Map generate(E_MapType type, short width, short height);
};

#endif
