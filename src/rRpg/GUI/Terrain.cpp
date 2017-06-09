#include "GUI/Terrain.hpp"
#include "SDL2_framework/TextureManager.h"
#include "SDL2_framework/Game.h"

void GraphicTerrain::render(
	TextureManager *manager,
	Game *game,
	int displayShiftX,
	int displayShiftY,
	S_TileData tileData,
	t_coordinates tilePosition
) {
	int xScreen = tilePosition.first * tileData.width - displayShiftX,
		yScreen = tilePosition.second * tileData.height - displayShiftY;

	// the rows are 1 based, and the columns are 0 based, which is
	// stupid
	manager->drawTile(
		tileData.tileset,
		0, // margin
		0, // spacing
		xScreen,
		yScreen,
		tileData.width,
		tileData.height,
		tileData.y + 1,
		tileData.x,
		game->getRenderer()
	);
}
