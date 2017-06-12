#ifndef __GRAPHIC_ACTOR__
#define __GRAPHIC_ACTOR__

#include "GUI.hpp"

class Actor;
class TextureManager;
class Game;

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
