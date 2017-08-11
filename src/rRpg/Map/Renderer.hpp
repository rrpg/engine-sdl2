#ifndef __MAP_RENDERER__
#define __MAP_RENDERER__

#include "types.hpp"
#include "GUI/Factory.hpp"
#include <SDL2/SDL.h>

class Map;
class Vector2D;
class FieldOfView;
class TextureManager;
class Game;

class MapRenderer {
	private:
	SDL_Rect m_camera = {};
	Map &m_map;
	GraphicFactory &m_graphicFactory;

	void _renderTerrain(TextureManager *manager, Game *game, FieldOfView &fov, int displayShiftX, int displayShiftY, int x, int y);
	void _renderObjects(TextureManager *manager, Game *game, int displayShiftX, int displayShiftY, int x, int y);
	void _renderActors(int displayShiftX, int displayShiftY, int x, int y);
	int _getMaskVisibleNeighbours(FieldOfView &fov, int x, int y);

	public:
	MapRenderer(Map &map, GraphicFactory &graphicFactory);
	void setCamera(SDL_Rect camera);
	void render(FieldOfView &fov);
};

#endif
