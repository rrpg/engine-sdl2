#ifndef __HUD__
#define __HUD__

#include "Actor.hpp"
#include "SDL2_framework/Game.h"
#include <memory>

class HUD {
	public:
	static void render(Game *game, std::shared_ptr<Actor> hero);
};

#endif
