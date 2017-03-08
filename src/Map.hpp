#ifndef __MAP__
#define __MAP__

#include "FileParser.hpp"
#include "ActorFactory.hpp"
#include <stdint.h>
#include <vector>
#include <unordered_map>
#include "SDL2_framework/Level.h"
#include "SDL2_framework/Vector2D.h"
#include <SDL2/SDL.h>

enum E_CellType {
	Wall, // 0
	Path, // 1
	Grass
};

class Map {
	private:
	unsigned int m_iWidth = 0;
	unsigned int m_iHeight = 0;
	Vector2D m_sStartPoint = Vector2D();
	Tileset m_tileset = Tileset();
	std::vector<int> m_vGrid = {};
	std::unordered_map<std::string, Actor*> m_mActors = {};
	std::unordered_map<E_CellType, int> m_mCellTypeFlags = {};
	std::vector<int> m_vEnemySpawnableCells = {};

	void _renderTerrain(SDL_Rect camera, SDL_Rect visibleArea, Vector2D shift);
	void _renderActors(SDL_Rect camera, SDL_Rect visibleArea, Vector2D shift);

	public:
	Map();
	~Map();
	static std::string getCoordsKey(int x, int y);
	E_FileParsingResult setMap(const char* mapFile);
	Vector2D getStartPoint();
	void addActor(Actor *actor);
	void render(SDL_Rect camera, int centerX, int centerY);
	bool isCellWalkable(int x, int y);
	std::unordered_map<std::string, Actor*> &getActors();
	void moveActor(Actor* actor, int newX, int newY);
	void setStartPoint(float x, float y);
	void setDimensions(unsigned int x, unsigned int y);
	void setTileset(Tileset tileset);
	void addEnemySpawnableCell(int cellIndex);
	std::vector<int>* getGrid();
	void initEnemies(ActorFactory &actorFactory);
};

#endif
