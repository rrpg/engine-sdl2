#ifndef __GRAPHIC_PLAYER__
#define __GRAPHIC_PLAYER__

#include "Actor.hpp"

class GraphicPlayer : public GraphicActor {
	protected:
	void _renderHP(unsigned int displayShiftX, unsigned int displayShiftY, Actor *actor);
};

#endif
