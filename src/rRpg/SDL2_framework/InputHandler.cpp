#include "InputHandler.h"
#include <iostream>
#include <SDL2/SDL.h>

static InputHandler* s_pInstance;

/**
 * Construct. Enable the SDL Joystick event state. This will then reacts to
 * joystick events.
 */
InputHandler::InputHandler() {
	SDL_JoystickEventState(SDL_ENABLE);
}

/**
 * Singleton method to get the instance.
 */
InputHandler *InputHandler::Instance() {
	if (s_pInstance == 0) {
		s_pInstance = new InputHandler();
	}

	return s_pInstance;
}

/**
 * Processes the SDL events and acts accordingly depending on the event type.
 */
InputUpdateResult InputHandler::update() {
	InputUpdateResult ret = HAS_NO_EVENT;
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		ret = HAS_EVENT;
		switch (event.type) {
			case SDL_QUIT:
				ret = QUIT;
				break;
			case SDL_JOYAXISMOTION:
				_handleStickEvent(event);
				break;
			case SDL_JOYBUTTONDOWN:
				_handleButtonEvent(event, true);
				break;
			case SDL_JOYBUTTONUP:
				_handleButtonEvent(event, false);
				break;
			case SDL_JOYDEVICEADDED:
				_initialiseJoystick(event.cdevice.which);
				break;
			case SDL_JOYDEVICEREMOVED:
				_handleJoystickRemoved();
				break;
			case SDL_KEYDOWN:
				_handleKeyEvent(event, true);
				break;
			case SDL_KEYUP:
				_handleKeyEvent(event, false);
				break;
			default:
				ret = HAS_NO_EVENT;
				break;
		}
	}

	return ret;
}

/**
 * Set a joystick stick value depending on which stick is manipulated.
 */
void InputHandler::_handleStickEvent(const SDL_Event event) {
	int joystickId = event.jaxis.which;
	// left stick move left or right
	if (event.jaxis.axis == M_LEFT_STICK_X_AXIS) {
		_setJoystickValue(event.jaxis.value, &m_mJoystickAxisValues[joystickId].first, VECTOR_X);
	}
	// left stick move up or down
	if (event.jaxis.axis == M_LEFT_STICK_Y_AXIS) {
		_setJoystickValue(event.jaxis.value, &m_mJoystickAxisValues[joystickId].first, VECTOR_Y);
	}
	// right stick move left or right
	if (event.jaxis.axis == M_RIGHT_STICK_X_AXIS) {
		_setJoystickValue(event.jaxis.value, &m_mJoystickAxisValues[joystickId].second, VECTOR_X);
	}
	// right stick move up or down
	if (event.jaxis.axis == M_RIGHT_STICK_Y_AXIS) {
		_setJoystickValue(event.jaxis.value, &m_mJoystickAxisValues[joystickId].second, VECTOR_Y);
	}
}

/**
 * Change the state of a pressed or released joystick button.
 */
void InputHandler::_handleButtonEvent(const SDL_Event event, const bool isDown) {
	int joystickId = event.jaxis.which;
	m_mButtonStates[joystickId][event.jbutton.button] = isDown;
}

/**
 * Change the state of a pressed or released keyboard key.
 */
void InputHandler::_handleKeyEvent(const SDL_Event event, const bool isDown) {
	m_mKeysStates[event.key.keysym.scancode] = isDown;
}

/**
 * If a joystick is removed, completely clean the list of joysticks
 */
void InputHandler::_handleJoystickRemoved() {
	clean();
}

/**
 * Set the value 1, -1 or 0 to a stick axis vector depending on the position of
 * the stick. 1 and -1 being on either side of the dead zone and 0 being within
 * the dead zone (stick considered as in neutral position).
 */
void InputHandler::_setJoystickValue(const int value, Vector2D* axisVector, Vector2DCoord coord) {
	if (value > M_JOYSTICK_DEADZONE) {
		axisVector->set(coord, 1.0);
	}
	else if (value < -M_JOYSTICK_DEADZONE) {
		axisVector->set(coord, -1.0);
	}
	else {
		axisVector->set(coord, 0.0);
	}
}

/**
 * Initialises a joystick, creates the maps and vectors to monitor its buttons
 * and sticks.
 */
void InputHandler::_initialiseJoystick(const int indexJoystick) {
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	SDL_Joystick* joy = SDL_JoystickOpen(indexJoystick);
	if (!joy) {
		std::cout << SDL_GetError();
	}
	else {
		int joystickId = SDL_JoystickInstanceID(joy);
		m_vJoysticks.push_back(std::make_pair(joystickId, joy));
		// for each joystick store their stick axises values
		m_mJoystickAxisValues[joystickId] = std::make_pair(
			Vector2D(0,0),
			Vector2D(0,0)
		);
		std::vector<bool> tempButtons;
		for (int j = 0; j < SDL_JoystickNumButtons(joy); j++) {
			tempButtons.push_back(false);
		}
		m_mButtonStates[joystickId] = tempButtons;
		m_bJoysticksInitialised = true;
		std::cout << "Initialised "<< m_vJoysticks.size() << " joystick(s)\n";
	}
}

/**
 * Clears every initialised joysticks.
 */
void InputHandler::clean() {
	if (m_bJoysticksInitialised) {
		unsigned long nbJoysticks = m_vJoysticks.size();
		for (unsigned long i = 0; i < nbJoysticks; i++){
			SDL_JoystickClose(m_vJoysticks[i].second);
			m_vJoysticks[i].second = NULL;
		}

		std::cout << "Cleaned "<< m_vJoysticks.size() << " joystick(s)\n";
		m_vJoysticks.clear();
		m_mButtonStates.clear();
		m_mJoystickAxisValues.clear();

		m_bJoysticksInitialised = false;
	}
}

bool InputHandler::joysticksInitialised() {
	return m_bJoysticksInitialised;
}

void InputHandler::free() {
	delete s_pInstance;
	s_pInstance = 0;
}

/**
 * Gets the Y value of the required stick
 */
int InputHandler::stickValue(const unsigned long joyIndex, const JoystickControl stick) {
	int value = 0;
	if (m_mJoystickAxisValues.size() > 0) {
		if (stick == LEFT_STICK_X) {
			value = (int) m_mJoystickAxisValues[m_vJoysticks[joyIndex].first].first.getX();
		}
		else if (stick == LEFT_STICK_Y) {
			value = (int) m_mJoystickAxisValues[m_vJoysticks[joyIndex].first].first.getY();
		}
		else if (stick == RIGHT_STICK_X) {
			value = (int) m_mJoystickAxisValues[m_vJoysticks[joyIndex].first].second.getX();
		}
		else if (stick == RIGHT_STICK_Y) {
			value = (int) m_mJoystickAxisValues[m_vJoysticks[joyIndex].first].second.getY();
		}
	}
	return value;
}

bool InputHandler::getButtonState(const unsigned long joystickIndex, const unsigned long buttonNumber) {
	return m_mButtonStates[m_vJoysticks[joystickIndex].first][buttonNumber];
}

void InputHandler::setButtonState(const unsigned long joystickIndex, const unsigned long button, const bool down) {
	m_mButtonStates[m_vJoysticks[joystickIndex].first][button] = down;
}

bool InputHandler::getKeyState(const SDL_Scancode key) {
	return m_mKeysStates[key];
}

void InputHandler::setKeyState(const SDL_Scancode key, bool value) {
	m_mKeysStates[key] = value;
}
