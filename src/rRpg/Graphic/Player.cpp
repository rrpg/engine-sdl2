#include "Player.hpp"
#include "../Actor.hpp"

const unsigned int HP_HEIGHT = 16;

void GraphicPlayer::_renderHP(unsigned int displayShiftX, unsigned int displayShiftY, Actor *actor) {
	unsigned int leftMargin = 10;
	unsigned int maxHealthWidth = m_game->getScreenWidth() / 4 - leftMargin;
	displayShiftX = leftMargin;
	displayShiftY = m_game->getScreenHeight() - 10 - HP_HEIGHT;
	SDL_Rect r;
	r.x = displayShiftX;
	r.y = displayShiftY;
	r.w = maxHealthWidth * actor->getHealth() / actor->getMaxHealth();
	r.h = HP_HEIGHT;
	SDL_SetRenderDrawColor(m_game->getRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(m_game->getRenderer(), &r);
	r.w = maxHealthWidth;
	SDL_SetRenderDrawColor(m_game->getRenderer(), 0, 0, 0, 255);
	SDL_RenderDrawRect(m_game->getRenderer(), &r);
}
