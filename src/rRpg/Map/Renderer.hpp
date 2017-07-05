#ifndef __MAP_RENDERER__
#define __MAP_RENDERER__

#include "types.hpp"
#include "GUI/Factory.hpp"
#include <SDL2/SDL.h>

class Map;
class Vector2D;

class MapRenderer {
	private:
	SDL_Rect m_camera = {};
	Map &m_map;
	GraphicFactory &m_graphicFactory;

	void _renderTerrain(SDL_Rect visibleArea, Vector2D shift);
	void _renderObjects(SDL_Rect visibleArea, Vector2D shift);
	void _renderActors(SDL_Rect visibleArea, Vector2D shift);

	public:
	MapRenderer(Map &map, GraphicFactory &graphicFactory);
	void setCamera(SDL_Rect camera);
	void render(t_coordinates center);
};

#endif
