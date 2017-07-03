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

void MapRenderer::render(
	SDL_Rect camera,
	Map &map,
	GraphicFactory &graphicFactory,
	t_coordinates center
) {
	// x,y coords in the grid
	int cameraWidthGrid = camera.w / DISPLAY_TILE_WIDTH,
		cameraHeightGrid = camera.h / DISPLAY_TILE_HEIGHT;

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

	_renderTerrain(camera, map, graphicFactory, visibleArea, shift);
	_renderObjects(camera, map, graphicFactory, visibleArea, shift);
	_renderActors(camera, map, visibleArea, shift);
}

void MapRenderer::_renderTerrain(
	SDL_Rect camera,
	Map &map,
	GraphicFactory &graphicFactory,
	SDL_Rect visibleArea,
	Vector2D shift
) {
	// camera is in pixels in the window
	TextureManager *manager = TextureManager::Instance();
	Game *game = Game::Instance();

	int displayShiftX = (int) shift.getX() + camera.x;
	int displayShiftY = (int) shift.getY() + camera.y;
	for (int y = visibleArea.y; y < visibleArea.y + visibleArea.h; ++y) {
		for (int x = visibleArea.x; x < visibleArea.x + visibleArea.w; ++x) {
			if (!map.areCoordinatesValid(x, y)) {
				continue;
			}

			S_TileData tileData = map.getTerrainTileData(x, y);
			t_coordinates position = {x, y};
			graphicFactory.getGraphicTerrain()->render(
				manager,
				game,
				displayShiftX,
				displayShiftY,
				tileData,
				position
			);
		}
	}
}

void MapRenderer::_renderObjects(
	SDL_Rect camera,
	Map &map,
	GraphicFactory &graphicFactory,
	SDL_Rect visibleArea,
	Vector2D shift
) {
	TextureManager *manager = TextureManager::Instance();
	Game *game = Game::Instance();
	int displayShiftX = camera.x - (int) shift.getX();
	int displayShiftY = camera.y - (int) shift.getY();
	for (auto object : map.getObjects()) {
		t_coordinates objectPosition = object.second.first;
		if ((visibleArea.x > 0 && objectPosition.first < visibleArea.x)
				|| objectPosition.first > (visibleArea.x + visibleArea.w)
			|| (visibleArea.y > 0 && objectPosition.second < visibleArea.y)
				|| objectPosition.second > (visibleArea.y + visibleArea.h)
		) {
			continue;
		}

		S_ObjectData objectData = map.getObjectData(object.second.second);
		graphicFactory.getGraphicObject()->render(
			manager,
			game,
			displayShiftX,
			displayShiftY,
			objectData,
			objectPosition
		);
	}
}

void MapRenderer::_renderActors(SDL_Rect camera, Map &map, SDL_Rect visibleArea, Vector2D shift) {
	int displayShiftX = camera.x - (int) shift.getX();
	int displayShiftY = camera.y - (int) shift.getY();
	for (auto actor : map.getActors()) {
		if ((visibleArea.x > 0 && actor.second->getX() < visibleArea.x)
				|| actor.second->getX() > (visibleArea.x + visibleArea.w)
			|| (visibleArea.y > 0 && actor.second->getY() < visibleArea.y)
				|| actor.second->getY() > (visibleArea.y + visibleArea.h)
		) {
			continue;
		}

		actor.second->render(
			displayShiftX,
			displayShiftY
		);
	}
}
