#ifndef __MAP__
#define __MAP__

#include <memory>
#include <stdint.h>
#include <vector>
#include <unordered_map>
#include <SDL2/SDL.h>
#include "Terrain.hpp"
#include "Map/Event.hpp"
#include "types.hpp"
#include "GUI/Factory.hpp"
#include "ResourceManager.hpp"
#include "SDL2_framework/Vector2D.h"

class Actor;
class ActorFactory;
class MapEvent;
class Vector2D;

const int WALKABLE_CONSTRAINT_ACTOR_IS_BLOCKING = 0x1;
const int WALKABLE_CONSTRAINT_ACTOR_SPAWN_LOCATION = 0x2;

class Map {
	private:
	static MyUnorderedMap<E_MapType, std::vector<S_EnemyProbability>> s_mEnemiesPerMapType;

	E_MapType m_type = DEFAULT;
	std::string m_sName = "";
	int m_iLevel = 0;
	int m_iWidth = 0;
	int m_iHeight = 0;
	int m_iDisplayTileWidth = 0;
	int m_iDisplayTileHeight = 0;
	Vector2D m_sStartPoint;
	std::vector<E_TerrainType> m_vGrid;
	MyUnorderedMap<E_TerrainType, Terrain*> m_mTerrains;
	MyUnorderedMap<E_TerrainTile, S_TileData> m_mTerrainsTileData;
	std::unordered_map<std::string, std::shared_ptr<Actor>> m_mActors;
	std::unordered_map<std::string, std::pair<t_coordinates, MapEvent>> m_mEvents;
	std::unordered_map<std::string, std::pair<t_coordinates, E_Object>> m_mObjects;
	std::vector<t_coordinates> m_vEnemySpawnableCells;

	GraphicFactory &m_graphicFactory;

	ResourceManager<S_TileData> m_tilesManager;
	ResourceManager<S_ObjectData> m_objectsManager;

	static void _initEnemiesPerMapType();
	Terrain *_getTerrain(E_TerrainType type);
	S_TileData _getTerrainTileData(const E_TerrainTile tile);
	S_ObjectData _getObjectData(const E_Object objectType);
	void _renderTerrain(SDL_Rect camera, SDL_Rect visibleArea, Vector2D shift);
	void _renderObjects(SDL_Rect camera, SDL_Rect visibleArea, Vector2D shift);
	void _renderActors(SDL_Rect camera, SDL_Rect visibleArea, Vector2D shift);
	static std::string _getCoordsKey(int x, int y);
	int _getSameNeighbours(int x, int y);

	public:
	Map(GraphicFactory &graphicFactory);
	~Map();

	void clear();
	void setName(std::string name);
	void setLevel(int level);
	std::string getName();
	int getLevel();

	void initializeGrid(E_TerrainType type);
	void setType(E_MapType type);
	void setTileFile(const char *tileFilePath);
	void setObjectsFile(const char *objectsFilePath);
	void setDimensions(int x, int y);
	void setDisplayTileDimensions(int w, int h);
	void setTile(int x, int y, E_TerrainType type);
	void setStartPoint(float x, float y);

	void clearDeadActors();

	bool areCoordinatesValid(int x, int y);
	bool isCellWalkable(int x, int y, unsigned int walkableConstraint = 0);
	bool isCellObstructingView(int x, int y);
	E_MapType getType();
	Vector2D getStartPoint();
	int getDisplayTileWidth();
	int getDisplayTileHeight();
	std::vector<E_TerrainType>* getGrid();
	void setGrid(std::vector<E_TerrainType> grid);

	int getWidth();
	int getHeight();

	E_TerrainType getTile(int x, int y);
	size_t getTileIndex(int x, int y);
	void addActor(std::shared_ptr<Actor> actor);
	std::unordered_map<std::string, std::shared_ptr<Actor>> &getActors();
	std::shared_ptr<Actor> getActorAt(int x, int y);
	bool moveActor(Actor* actor, int newX, int newY);

	void render(SDL_Rect camera, int centerX, int centerY);

	void addEnemySpawnableCell(char x, char y);
	std::vector<t_coordinates> getEnemySpawnableCells();
	void initEnemies(ActorFactory &actorFactory);

	MapEvent *getEvent(const int x, const int y);
	void addEvent(const int x, const int y, MapEvent event);
	std::unordered_map<std::string, std::pair<t_coordinates, MapEvent>> &getEvents();

	void addObject(int x, int y, E_Object object);
	std::unordered_map<std::string, std::pair<t_coordinates, E_Object>> getObjects();
};

#endif
