#ifndef __GRAPHIC_ACTOR__
#define __GRAPHIC_ACTOR__

#include "Graphic.hpp"

class Actor;

class GraphicActor : public Graphic {
	public:
	~GraphicActor();
	void render(
		unsigned int displayShiftX,
		unsigned int displayShiftY,
		Actor *actor
	);
};

#endif
