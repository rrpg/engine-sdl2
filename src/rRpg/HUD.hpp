#ifndef __HUD__
#define __HUD__

#include "Actor.hpp"
#include "SDL2_framework/Game.h"

class HUD {
	public:
	static void render(Game *game, Actor *hero);
};

#endif
