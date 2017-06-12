#include "GUI/Object.hpp"
#include "SDL2_framework/TextureManager.h"

void GraphicObject::render(
	TextureManager *textureManager,
	Game *game,
	int displayShiftX,
	int displayShiftY,
	S_ObjectData objectData,
	t_coordinates objectCoordinates
) {
	int xScreen = objectCoordinates.first * TILE_WIDTH + displayShiftX;
	int yScreen = objectCoordinates.second * TILE_HEIGHT + displayShiftY;
	textureManager->drawTile(
		objectData.tileset,
		0, // margin
		0, // spacing
		xScreen,
		yScreen,
		TILE_WIDTH,
		TILE_HEIGHT,
		objectData.spriteY + 1,
		objectData.spriteX,
		game->getRenderer()
	);
}
