#ifndef __MAP__
#define __MAP__

#include "Parser/File.hpp"
#include "ActorFactory.hpp"
#include "Terrain.hpp"
#include <stdint.h>
#include <vector>
#include <unordered_map>
#include "SDL2_framework/Vector2D.h"
#include <SDL2/SDL.h>

struct EnumClassHash {
	template <typename T>
	std::size_t operator()(T t) const {
		return static_cast<std::size_t>(t);
	}
};

class Map {
	private:
	unsigned int m_iWidth = 0;
	unsigned int m_iHeight = 0;
	int m_iDisplayTileWidth = 0;
	int m_iDisplayTileHeight = 0;
	Vector2D m_sStartPoint = Vector2D();
	std::vector<E_TerrainType> m_vGrid = {};
	std::unordered_map<E_TerrainType, Terrain*, EnumClassHash> m_mTerrains = {};
	std::unordered_map<E_TerrainTile, S_TileData, EnumClassHash> m_mTerrainsTileData = {};
	std::unordered_map<std::string, Actor*> m_mActors = {};
	std::vector<std::pair<char, char>> m_vEnemySpawnableCells = {};

	FILE *m_tilesFile = 0;

	Terrain *_getTerrain(E_TerrainType type);
	S_TileData _getTerrainTileData(const E_TerrainTile tile);
	void _renderTerrain(SDL_Rect camera, SDL_Rect visibleArea, Vector2D shift);
	void _renderActors(SDL_Rect camera, SDL_Rect visibleArea, Vector2D shift);
	static std::string _getCoordsKey(int x, int y);
	int _getSameNeighbours(unsigned int x, unsigned int y);

	public:
	~Map();

	void initializeGrid(E_TerrainType type);
	void setTileFile(const char *tileFilePath);
	void setDimensions(unsigned int x, unsigned int y);
	void setDisplayTileDimensions(unsigned int w, unsigned int h);
	void setTile(int x, int y, E_TerrainType type);
	void setStartPoint(float x, float y);

	void clearDeadActors();

	bool isCellWalkable(int x, int y);
	bool isCellObstructingView(int x, int y);
	Vector2D getStartPoint();
	unsigned int getDisplayTileWidth();
	unsigned int getDisplayTileHeight();
	std::vector<E_TerrainType>* getGrid();
	void setGrid(std::vector<E_TerrainType> grid);

	unsigned int getWidth();
	unsigned int getHeight();

	E_TerrainType getTile(int x, int y);
	void addActor(Actor *actor);
	std::unordered_map<std::string, Actor*> &getActors();
	Actor *getActorAt(int x, int y);
	void moveActor(Actor* actor, int newX, int newY);

	void render(SDL_Rect camera, int centerX, int centerY);

	void addEnemySpawnableCell(char x, char y);
	std::vector<std::pair<char, char>> getEnemySpawnableCells();
	void initEnemies(ActorFactory &actorFactory);
};

#endif
