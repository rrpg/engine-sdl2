#ifndef __GRAPHIC_TERRAIN__
#define __GRAPHIC_TERRAIN__

#include "GUI.hpp"
#include "types.hpp"

class TextureManager;
class Game;

class GraphicTerrain : public Graphic {
	public:
	void render(
		TextureManager *manager,
		Game *game,
		int displayShiftX,
		int displayShiftY,
		S_TileData tileData,
		t_coordinates tilePosition
	);
};

#endif
