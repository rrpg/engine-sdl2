#ifndef __MAP_GENERATOR__
#define __MAP_GENERATOR__

#include <string>
#include <vector>
#include "CaveRoom.hpp"
#include "types.hpp"

class Map;

class MapGenerator {
	private:
	Map &m_map;

	void _generateCave(S_MapSpecs specs);
	void _initialiseAutomaton();
	void _automatonStep();
	void _joinRooms();
	void _cleanRooms();
	std::vector<CaveRoom::S_Room>::iterator _largestRoom(std::vector<CaveRoom::S_Room> &rooms);
	size_t _digBetweenRooms(CaveRoom::S_RoomCollection &roomCollection, size_t cell1Index, size_t cell2Index);
	int _getCountAliveNeighbours(int i, int j, E_TerrainType aliveType);
	void _setStartPoint();
	std::vector<t_coordinates> _findWalkableNeighbours(const int x, const int y);
	bool _findClosestWalkableCell(
		const int x,
		const int y,
		std::vector<bool> &visited,
		int &xOut,
		int &yOut
	);
	void _dispatchEnemies(const int nbMaxEnemies);
	void _addStair(int direction, int x = -1, int y = -1);

	public:
	MapGenerator(Map &map);
	void generate(S_MapSpecs specs);
};

#endif
