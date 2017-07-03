#ifndef __MAP_RENDERER__
#define __MAP_RENDERER__

#include "types.hpp"
#include "GUI/Factory.hpp"
#include <SDL2/SDL.h>

class Map;
class Vector2D;

class MapRenderer {
	private:
	static void _renderTerrain(SDL_Rect, Map&, GraphicFactory&, SDL_Rect, Vector2D);
	static void _renderObjects(SDL_Rect, Map&, GraphicFactory&, SDL_Rect, Vector2D);
	static void _renderActors(SDL_Rect camera, Map &map, SDL_Rect visibleArea, Vector2D shift);

	public:
	static void render(SDL_Rect camera, Map &map, GraphicFactory &graphicFactory, t_coordinates center);
};

#endif
