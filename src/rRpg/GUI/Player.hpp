#ifndef __GRAPHIC_PLAYER__
#define __GRAPHIC_PLAYER__

#include "GUI/Actor.hpp"

class Actor;

class GraphicPlayer : public GraphicActor {
	protected:
	void render(int displayShiftX, int displayShiftY, Actor *actor);
};

#endif
