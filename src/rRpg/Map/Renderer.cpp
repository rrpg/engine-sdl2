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

	_renderTerrain(fov, shift);
	_renderObjects(fov, shift);
	_renderActors(fov, shift);
}

void MapRenderer::_renderTerrain(FieldOfView &fov, Vector2D shift) {
	// camera is in pixels in the window
	TextureManager *manager = TextureManager::Instance();
	Game *game = Game::Instance();

	int displayShiftX = (int) shift.getX() + m_camera.x;
	int displayShiftY = (int) shift.getY() + m_camera.y;
	for (auto cell : fov.getVisibleCells()) {
		int x = cell.first.first,
			y = cell.first.second;
		if (!cell.second) {
			continue;
		}

		int mask = _getMaskVisibleNeighbours(fov, x, y);
		S_TileData tileData = m_map.getTerrainTileData(mask, x, y);
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

int MapRenderer::_getMaskVisibleNeighbours(FieldOfView &fov, int x, int y) {
	int width = fov.getVisibleArea().w,
		height = fov.getVisibleArea().h;
	int nbNeighbours = (y == 0 || !fov.isVisible(x, y - 1)) // north
		+ NEIGHBOUR_WEST * (x == 0 || !fov.isVisible(x - 1, y)) // west
		+ NEIGHBOUR_EAST * (x == width - 1 || !fov.isVisible(x + 1, y)) // east
		+ NEIGHBOUR_SOUTH * (y == height - 1 || !fov.isVisible(x, y + 1)); // south

	return nbNeighbours;
}

void MapRenderer::_renderObjects(FieldOfView &fov, Vector2D shift) {
	TextureManager *manager = TextureManager::Instance();
	Game *game = Game::Instance();
	int displayShiftX = m_camera.x - (int) shift.getX();
	int displayShiftY = m_camera.y - (int) shift.getY();
	for (auto cell : fov.getVisibleCells()) {
		int x = cell.first.first,
			y = cell.first.second;

		E_Object *object = m_map.getObjectAt(x, y);
		if (object == NULL || !cell.second) {
			continue;
		}

		S_ObjectData objectData = m_map.getObjectData(*object);
		m_graphicFactory.getGraphicObject()->render(
			manager,
			game,
			displayShiftX,
			displayShiftY,
			objectData,
			cell.first
		);
	}
}

void MapRenderer::_renderActors(FieldOfView &fov, Vector2D shift) {
	int displayShiftX = m_camera.x - (int) shift.getX();
	int displayShiftY = m_camera.y - (int) shift.getY();
	for (auto cell : fov.getVisibleCells()) {
		int x = cell.first.first,
			y = cell.first.second;

		std::shared_ptr<Actor> actor = m_map.getActorAt(x, y);
		if (actor == NULL || !cell.second) {
			continue;
		}

		actor->render(displayShiftX, displayShiftY);
	}
}
