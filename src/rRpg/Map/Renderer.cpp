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
	m_camera(),
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

	// camera is in pixels in the window
	TextureManager *manager = TextureManager::Instance();
	Game *game = Game::Instance();

	int displayShiftX = m_camera.x - (int) shift.getX();
	int displayShiftY = m_camera.y - (int) shift.getY();
	for (auto cell : fov.getVisibleCells()) {
		int x = cell.first,
			y = cell.second;
		_renderTerrain(manager, game, fov, displayShiftX, displayShiftY, x, y);
		_renderObjects(manager, game, displayShiftX, displayShiftY, x, y);
		_renderActors(displayShiftX, displayShiftY, x, y);
	}
}

void MapRenderer::_renderTerrain(
	TextureManager *manager, Game *game,
	FieldOfView &fov,
	int displayShiftX, int displayShiftY,
	int x, int y
) {
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

int MapRenderer::_getMaskVisibleNeighbours(FieldOfView &fov, int x, int y) {
	int width = fov.getVisibleArea().w,
		height = fov.getVisibleArea().h;
	int nbNeighbours = (y == 0 || !fov.isVisible(x, y - 1)) // north
		+ NEIGHBOUR_WEST * (x == 0 || !fov.isVisible(x - 1, y)) // west
		+ NEIGHBOUR_EAST * (x == width - 1 || !fov.isVisible(x + 1, y)) // east
		+ NEIGHBOUR_SOUTH * (y == height - 1 || !fov.isVisible(x, y + 1)); // south

	return nbNeighbours;
}

void MapRenderer::_renderObjects(
	TextureManager *manager, Game *game,
	int displayShiftX, int displayShiftY,
	int x, int y
) {
	E_Object *object = m_map.getObjectAt(x, y);
	if (object == NULL) {
		return;
	}

	S_ObjectData objectData = m_map.getObjectData(*object);
	t_coordinates position = {x, y};
	m_graphicFactory.getGraphicObject()->render(
		manager,
		game,
		displayShiftX,
		displayShiftY,
		objectData,
		position
	);
}

void MapRenderer::_renderActors(int displayShiftX, int displayShiftY, int x, int y) {
	std::shared_ptr<Actor> actor = m_map.getActorAt(x, y);
	if (actor == NULL) {
		return;
	}

	actor->render(displayShiftX, displayShiftY);
}
