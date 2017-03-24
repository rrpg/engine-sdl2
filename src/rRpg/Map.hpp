#ifndef __MAP__
#define __MAP__

#include "Parser/File.hpp"
#include "ActorFactory.hpp"
#include "Terrain.hpp"
#include <stdint.h>
#include <vector>
#include <unordered_map>
#include "SDL2_framework/Level.h"
#include "SDL2_framework/Vector2D.h"
#include <SDL2/SDL.h>

class Map {
	private:
	unsigned int m_iWidth = 0;
	unsigned int m_iHeight = 0;
	Vector2D m_sStartPoint = Vector2D();
	std::vector<Tileset> m_vTilesets = {};
	std::vector<E_TerrainType> m_vGrid = {};
	std::unordered_map<E_TerrainType, Terrain*> m_mTerrains = {};
	std::unordered_map<std::string, Actor*> m_mActors = {};
	std::vector<int> m_vEnemySpawnableCells = {};

	FILE *m_tilesFile = 0;

	Terrain *_getTerrain(E_TerrainType type);
	void _renderTerrain(SDL_Rect camera, SDL_Rect visibleArea, Vector2D shift);
	void _renderActors(SDL_Rect camera, SDL_Rect visibleArea, Vector2D shift);

	public:
	~Map();
	void setTileFile(const char *tileFilePath);
	void setDimensions(unsigned int x, unsigned int y);
	void clearDeadActors();
	static std::string getCoordsKey(int x, int y);
	E_FileParsingResult setMap(const char* mapFile);
	Vector2D getStartPoint();

	bool isCellWalkable(int x, int y);
	bool isCellObstructingView(int x, int y);
	std::vector<E_TerrainType>* getGrid();

	void addActor(Actor *actor);
	std::unordered_map<std::string, Actor*> &getActors();
	Actor *getActorAt(int x, int y);
	void moveActor(Actor* actor, int newX, int newY);
	void setStartPoint(float x, float y);

	void addTileset(Tileset tileset);
	void render(SDL_Rect camera, int centerX, int centerY);

	void addEnemySpawnableCell(int cellIndex);
	void initEnemies(ActorFactory &actorFactory);
};

#endif
