#include "Player.hpp"
#include "../Actor.hpp"

void GraphicPlayer::render(int displayShiftX, int displayShiftY, Actor *actor) {
	_renderActor(displayShiftX, displayShiftY, actor);
}
