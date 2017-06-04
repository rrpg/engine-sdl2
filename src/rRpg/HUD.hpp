#ifndef __HUD__
#define __HUD__

#include <memory>

class Actor;
class Game;

class HUD {
	public:
	static void render(Game *game, std::shared_ptr<Actor> hero);
};

#endif
