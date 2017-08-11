#ifndef __MAP_RENDERER__
#define __MAP_RENDERER__

#include "types.hpp"
#include "GUI/Factory.hpp"
#include <SDL2/SDL.h>

class Map;
class Vector2D;
class FieldOfView;

class MapRenderer {
	private:
	SDL_Rect m_camera = {};
	Map &m_map;
	GraphicFactory &m_graphicFactory;

	void _renderTerrain(FieldOfView &fov, Vector2D shift);
	void _renderObjects(FieldOfView &fov, Vector2D shift);
	void _renderActors(FieldOfView &fov, Vector2D shift);
	int _getMaskVisibleNeighbours(FieldOfView &fov, int x, int y);

	public:
	MapRenderer(Map &map, GraphicFactory &graphicFactory);
	void setCamera(SDL_Rect camera);
	void render(FieldOfView &fov);
};

#endif
