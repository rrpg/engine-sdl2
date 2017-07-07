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

	void _renderTerrain(std::vector<t_coordinates> fov, SDL_Rect visibleArea, Vector2D shift);
	void _renderObjects(std::vector<t_coordinates> fov, SDL_Rect visibleArea, Vector2D shift);
	void _renderActors(std::vector<t_coordinates> fov, SDL_Rect visibleArea, Vector2D shift);

	public:
	MapRenderer(Map &map, GraphicFactory &graphicFactory);
	void setCamera(SDL_Rect camera);
	void render(std::vector<t_coordinates> fov, t_coordinates center);
};

#endif
