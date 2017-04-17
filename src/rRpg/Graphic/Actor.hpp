#ifndef __GRAPHIC_ACTOR__
#define __GRAPHIC_ACTOR__

#include "Graphic.hpp"
#include "SDL2_framework/Game.h"
#include "SDL2_framework/TextureManager.h"

class Actor;

class GraphicActor : public Graphic {
	protected:
	TextureManager *m_textureManager = 0;
	Game *m_game = 0;

	public:
	GraphicActor();
	GraphicActor(const GraphicActor &L); // copy constructor
	GraphicActor & operator=(const GraphicActor &L); // assignment
	~GraphicActor();
	void render(
		unsigned int displayShiftX,
		unsigned int displayShiftY,
		Actor *actor
	);
};

#endif
