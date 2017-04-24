#include "HUD.hpp"

const int HP_HEIGHT = 16;

void HUD::render(Game *game, Actor *hero) {
	int leftMargin = 10;
	int maxHealthWidth = game->getScreenWidth() / 4 - leftMargin;
	int displayShiftX = leftMargin;
	int displayShiftY = game->getScreenHeight() - 10 - HP_HEIGHT;
	unsigned int health = 0;
	if (hero->getHealth() > 0) {
		health = (unsigned) hero->getHealth();
	}
	SDL_Rect r;
	r.x = displayShiftX;
	r.y = displayShiftY;
	r.w = (signed) ((unsigned) maxHealthWidth * health / hero->getMaxHealth());
	r.h = HP_HEIGHT;
	SDL_SetRenderDrawColor(game->getRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(game->getRenderer(), &r);
	r.w = maxHealthWidth;
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 255);
	SDL_RenderDrawRect(game->getRenderer(), &r);
}
