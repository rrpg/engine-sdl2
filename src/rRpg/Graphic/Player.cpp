#include "Player.hpp"
#include "../Actor.hpp"

void GraphicPlayer::render(unsigned int displayShiftX, unsigned int displayShiftY, Actor *actor) {
	_renderActor(displayShiftX, displayShiftY, actor);
}
