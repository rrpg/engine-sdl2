#include "Actor.hpp"
#include "../Actor.hpp"
#include "../ActorRace.hpp"

GraphicActor::GraphicActor() {
	m_textureManager = TextureManager::Instance();
	m_game = Game::Instance();
}

GraphicActor::GraphicActor(const GraphicActor &r) :
	m_textureManager(r.m_textureManager),
	m_game(r.m_game)
{
}

GraphicActor & GraphicActor::operator=(const GraphicActor &r) {
	// check for "self assignment" and do nothing in that case
	if (this == &r) {
		return *this;
	}

	m_textureManager = r.m_textureManager;
	m_game = r.m_game;
	return *this;
}

GraphicActor::~GraphicActor() {}

void GraphicActor::render(unsigned int displayShiftX, unsigned int displayShiftY, Actor *actor) {
	_renderActor(displayShiftX, displayShiftY, actor);
	_renderHP(displayShiftX, displayShiftY, actor);
}

void GraphicActor::_renderActor(unsigned int displayShiftX, unsigned int displayShiftY, Actor *actor) {
	unsigned int xScreen = actor->getX() * TILE_WIDTH + displayShiftX;
	unsigned int yScreen = actor->getY() * TILE_HEIGHT + displayShiftY;
	m_textureManager->drawTile(
		actor->getRace().getTilesetName(),
		0, // margin
		0, // spacing
		xScreen,
		yScreen,
		TILE_WIDTH,
		TILE_HEIGHT,
		(int) actor->getRace().getSpriteY() + 1,
		(int) actor->getRace().getSpriteX(),
		m_game->getRenderer(),
		actor->getOrientation() == RIGHT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
	);
}

void GraphicActor::_renderHP(unsigned int displayShiftX, unsigned int displayShiftY, Actor *actor) {
	unsigned int xScreen = actor->getX() * TILE_WIDTH + displayShiftX;
	unsigned int yScreen = actor->getY() * TILE_HEIGHT + displayShiftY;
	SDL_Rect r;
	r.x = xScreen;
	r.y = yScreen;
	r.w = TILE_WIDTH * actor->getHealth() / actor->getMaxHealth();
	r.h = 2;
	SDL_SetRenderDrawColor(m_game->getRenderer(), 0xff, 0, 0, 255);
	SDL_RenderFillRect(m_game->getRenderer(), &r);
}
