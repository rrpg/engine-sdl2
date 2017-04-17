#include "Actor.hpp"
#include "../Actor.hpp"
#include "../ActorRace.hpp"
#include "SDL2_framework/Game.h"
#include "SDL2_framework/TextureManager.h"

const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;

GraphicActor::~GraphicActor() {}

void GraphicActor::render(unsigned int displayShiftX, unsigned int displayShiftY, Actor *actor) {
	TextureManager *manager = TextureManager::Instance();
	Game *game = Game::Instance();
	unsigned int xScreen = actor->getX() * TILE_WIDTH + displayShiftX;
	unsigned int yScreen = actor->getY() * TILE_HEIGHT + displayShiftY;
	manager->drawTile(
		actor->getRace().getTilesetName(),
		0, // margin
		0, // spacing
		xScreen,
		yScreen,
		TILE_WIDTH,
		TILE_HEIGHT,
		(int) actor->getRace().getSpriteY() + 1,
		(int) actor->getRace().getSpriteX(),
		game->getRenderer()
	);

	// render HPs
	SDL_Rect r;
	r.x = xScreen;
	r.y = yScreen;
	r.w = TILE_WIDTH * actor->getHealth() / actor->getMaxHealth();
	r.h = 2;
	SDL_SetRenderDrawColor(game->getRenderer(), 0xff, 0, 0, 255);
	SDL_RenderFillRect(game->getRenderer(), &r);
}
