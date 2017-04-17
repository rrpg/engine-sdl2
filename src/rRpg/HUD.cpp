#include "HUD.hpp"

const unsigned int HP_HEIGHT = 16;

void HUD::render(Game *game, Actor *hero) {
	unsigned int leftMargin = 10;
	unsigned int maxHealthWidth = game->getScreenWidth() / 4 - leftMargin;
	unsigned int displayShiftX = leftMargin;
	unsigned int displayShiftY = game->getScreenHeight() - 10 - HP_HEIGHT;
	SDL_Rect r;
	r.x = displayShiftX;
	r.y = displayShiftY;
	r.w = maxHealthWidth * hero->getHealth() / hero->getMaxHealth();
	r.h = HP_HEIGHT;
	SDL_SetRenderDrawColor(game->getRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(game->getRenderer(), &r);
	r.w = maxHealthWidth;
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 255);
	SDL_RenderDrawRect(game->getRenderer(), &r);
}
