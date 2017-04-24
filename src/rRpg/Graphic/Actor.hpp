#ifndef __GRAPHIC_ACTOR__
#define __GRAPHIC_ACTOR__

#include "Graphic.hpp"
#include "SDL2_framework/Game.h"
#include "SDL2_framework/TextureManager.h"

const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;

class Actor;

class GraphicActor : public Graphic {
	protected:
	TextureManager *m_textureManager = 0;
	Game *m_game = 0;
	virtual void _renderActor(int displayShiftX, int displayShiftY, Actor *actor);
	virtual void _renderHP(int displayShiftX, int displayShiftY, Actor *actor);

	public:
	GraphicActor();
	GraphicActor(const GraphicActor &L); // copy constructor
	GraphicActor & operator=(const GraphicActor &L); // assignment
	~GraphicActor();
	virtual void render(
		int displayShiftX,
		int displayShiftY,
		Actor *actor
	);
};

#endif
