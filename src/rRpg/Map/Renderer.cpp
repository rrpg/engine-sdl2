#include "Map/Renderer.hpp"
#include "Map.hpp"
#include "GUI.hpp"
#include "Actor.hpp"
#include "GUI/Factory.hpp"
#include "GUI/Terrain.hpp"
#include "GUI/Object.hpp"
#include "SDL2_framework/Vector2D.h"

#define DISPLAY_TILE_WIDTH 16
#define DISPLAY_TILE_HEIGHT 16

MapRenderer::MapRenderer(Map &map, GraphicFactory &graphicFactory) :
	m_map(map),
	m_graphicFactory(graphicFactory)
{
}

void MapRenderer::setCamera(SDL_Rect camera) {
	m_camera = camera;
}

void MapRenderer::render(std::vector<t_coordinates> fov, t_coordinates center) {
	// x,y coords in the grid
	int cameraWidthGrid = m_camera.w / DISPLAY_TILE_WIDTH,
		cameraHeightGrid = m_camera.h / DISPLAY_TILE_HEIGHT;

	SDL_Rect visibleArea = {
		// portion of the map which is visible
		center.first - cameraWidthGrid / 2,
		center.second - cameraHeightGrid / 2,
		cameraWidthGrid,
		cameraHeightGrid
	};

	Vector2D shift = {
		(float) (visibleArea.x * DISPLAY_TILE_WIDTH),
		(float) (visibleArea.y * DISPLAY_TILE_HEIGHT)
	};

	_renderTerrain(fov, visibleArea, shift);
	_renderObjects(fov, visibleArea, shift);
	_renderActors(fov, visibleArea, shift);
}

void MapRenderer::_renderTerrain(std::vector<t_coordinates> fov, SDL_Rect visibleArea, Vector2D shift) {
	// camera is in pixels in the window
	TextureManager *manager = TextureManager::Instance();
	Game *game = Game::Instance();

	int displayShiftX = (int) shift.getX() + m_camera.x;
	int displayShiftY = (int) shift.getY() + m_camera.y;
	for (auto cell : fov) {
		int x = cell.first,
			y = cell.second;
		if (x < visibleArea.x || x > visibleArea.x + visibleArea.w
			|| y < visibleArea.y || y > visibleArea.y + visibleArea.h
		) {
			continue;
		}

		S_TileData tileData = m_map.getTerrainTileData(x, y);
		t_coordinates position = {x, y};
		m_graphicFactory.getGraphicTerrain()->render(
			manager,
			game,
			displayShiftX,
			displayShiftY,
			tileData,
			position
		);
	}
}

void MapRenderer::_renderObjects(std::vector<t_coordinates> fov, SDL_Rect visibleArea, Vector2D shift) {
	TextureManager *manager = TextureManager::Instance();
	Game *game = Game::Instance();
	int displayShiftX = m_camera.x - (int) shift.getX();
	int displayShiftY = m_camera.y - (int) shift.getY();
	for (auto cell : fov) {
		int x = cell.first,
			y = cell.second;

		E_Object *object = m_map.getObjectAt(x, y);
		if (object == NULL
			|| x < visibleArea.x || x > visibleArea.x + visibleArea.w
			|| y < visibleArea.y || y > visibleArea.y + visibleArea.h
		) {
			continue;
		}

		S_ObjectData objectData = m_map.getObjectData(*object);
		m_graphicFactory.getGraphicObject()->render(
			manager,
			game,
			displayShiftX,
			displayShiftY,
			objectData,
			cell
		);
	}
}

void MapRenderer::_renderActors(std::vector<t_coordinates> fov, SDL_Rect visibleArea, Vector2D shift) {
	int displayShiftX = m_camera.x - (int) shift.getX();
	int displayShiftY = m_camera.y - (int) shift.getY();
	for (auto cell : fov) {
		int x = cell.first,
			y = cell.second;

		std::shared_ptr<Actor> actor = m_map.getActorAt(x, y);
		if (actor == NULL
			|| x < visibleArea.x || x > visibleArea.x + visibleArea.w
			|| y < visibleArea.y || y > visibleArea.y + visibleArea.h
		) {
			continue;
		}

		actor->render(displayShiftX, displayShiftY);
	}
}
