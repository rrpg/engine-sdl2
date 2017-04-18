#include "NoJoystickState.h"
#include "Game.h"
#include "InputHandler.h"

const std::string NoJoystickState::s_menuID = "NO_JOYSTICK";

/**
 * If we are here, the joysticks are not initialised (no joystick), so the
 * update just checks if a joystick is plugged, if yes, then popped the current
 * state from the state machine (which is itself) to return to the previous
 * state.
 */
void NoJoystickState::update() {
	if (InputHandler::Instance()->joysticksInitialised()) {
		Game::Instance()->getStateMachine()->popState();
	}
}
void NoJoystickState::render() {
	// nothing for now
}
bool NoJoystickState::onEnter() {
	return true;
}
bool NoJoystickState::onExit() {
	return true;
}

std::string NoJoystickState::getStateID() const {
	return s_menuID;
}
