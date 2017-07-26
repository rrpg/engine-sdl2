#include "Map/Renderer.hpp"
#include "Map.hpp"
#include "GUI.hpp"
#include "Actor.hpp"
#include "GUI/Factory.hpp"
#include "FieldOfView.hpp"
#include "GUI/Terrain.hpp"
#include "GUI/Object.hpp"
#include "SDL2_framework/Vector2D.h"

MapRenderer::MapRenderer(Map &map, GraphicFactory &graphicFactory) :
	m_map(map),
	m_graphicFactory(graphicFactory)
{
}

void MapRenderer::setCamera(SDL_Rect camera) {
	m_camera = camera;
}

void MapRenderer::render(FieldOfView &fov) {
	SDL_Rect visibleArea = fov.getVisibleArea();
	Vector2D shift = {
		(float) (visibleArea.x * TILE_WIDTH),
		(float) (visibleArea.y * TILE_HEIGHT)
	};

	_renderTerrain(fov, visibleArea, shift);
	_renderObjects(fov, visibleArea, shift);
	_renderActors(fov, visibleArea, shift);
}

void MapRenderer::_renderTerrain(FieldOfView &fov, SDL_Rect visibleArea, Vector2D shift) {
	// camera is in pixels in the window
	TextureManager *manager = TextureManager::Instance();
	Game *game = Game::Instance();

	int displayShiftX = (int) shift.getX() + m_camera.x;
	int displayShiftY = (int) shift.getY() + m_camera.y;
	for (auto cell : fov.getVisibleCells()) {
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

void MapRenderer::_renderObjects(FieldOfView &fov, SDL_Rect visibleArea, Vector2D shift) {
	TextureManager *manager = TextureManager::Instance();
	Game *game = Game::Instance();
	int displayShiftX = m_camera.x - (int) shift.getX();
	int displayShiftY = m_camera.y - (int) shift.getY();
	for (auto cell : fov.getVisibleCells()) {
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

void MapRenderer::_renderActors(FieldOfView &fov, SDL_Rect visibleArea, Vector2D shift) {
	int displayShiftX = m_camera.x - (int) shift.getX();
	int displayShiftY = m_camera.y - (int) shift.getY();
	for (auto cell : fov.getVisibleCells()) {
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
