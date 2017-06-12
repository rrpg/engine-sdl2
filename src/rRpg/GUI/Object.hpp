#ifndef __GRAPHIC_OBJECT__
#define __GRAPHIC_OBJECT__

#include "GUI.hpp"
#include "SDL2_framework/Game.h"
#include "types.hpp"

class TextureManager;

class GraphicObject : public Graphic {
	public:
	void render(
		TextureManager *m_textureManager,
		Game *game,
		int displayShiftX,
		int displayShiftY,
		S_ObjectData objectData,
		t_coordinates objectCoordinates
	);
};

#endif
