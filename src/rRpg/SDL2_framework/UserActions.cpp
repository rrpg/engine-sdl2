#define _CRT_SECURE_NO_WARNINGS

#include "UserActions.h"
#include <fstream>
using std::ifstream;

#include <cstring>

const int MAX_CHAR_COMMAND = 128;
const int MAX_CHARS_PER_LINE = 134; // 128 + 6
const char* const DELIMITER = ";";

UserActions::UserActions() : m_mMappings({}) {}

void UserActions::add(std::string name, S_Command c) {
	if (!m_mMappings.count(name)) {
		std::vector<S_Command> tempCommands;
		m_mMappings[name] = tempCommands;
	}

	m_mMappings[name].push_back(c);
}

int UserActions::getActionState(std::string name) {
	if (!m_mMappings.count(name)) {
		return 0;
	}

	std::vector<S_Command> commands = m_mMappings[name];
	int ret = 0;
	InputHandler* handlerInstance = InputHandler::Instance();
	for (unsigned int c = 0; c < commands.size(); c++) {
		switch (commands[c].type) {
			case CONTROLLER_BUTTON:
				ret = !handlerInstance->joysticksInitialised() ? 0 :
					handlerInstance->getButtonState(0, commands[c].buttonId);
				break;
			case CONTROLLER_STICK:
				if (handlerInstance->joysticksInitialised()) {
					int stickValue = handlerInstance->stickValue(
						0, commands[c].stickAxis
					);
					int stickDirection = commands[c].stickDirection;
					if (stickDirection == 0 || stickValue == stickDirection) {
						ret = stickValue;
					}
				}
				break;
			case KEYBOARD_KEY:
				ret = handlerInstance->getKeyState(commands[c].key);
				break;
			case NULL_TYPE:
			default:
				break;
		}

		if (ret != 0) {
			break;
		}
	}

	return ret;
}

void UserActions::resetActionState(std::string name) {
	if (!m_mMappings.count(name)) {
		return;
	}

	std::vector<S_Command> commands = m_mMappings[name];
	InputHandler* handlerInstance = InputHandler::Instance();
	for (unsigned int c = 0; c < commands.size(); c++) {
		switch (commands[c].type) {
			case CONTROLLER_BUTTON:
				if (handlerInstance->joysticksInitialised()) {
					handlerInstance->setButtonState(
						0, commands[c].buttonId, false
					);
				}
				break;
			case KEYBOARD_KEY:
				handlerInstance->setKeyState(commands[c].key, false);
				break;
			case CONTROLLER_STICK:
			case NULL_TYPE:
			default:
				break;
		}
	}
}

int UserActions::setActionsFromFile(const char* mappingFile) {
	// create a file-reading object
	ifstream fin;
	fin.open(mappingFile); // open a file
	if (!fin.good()) {
		fin.close();
		return NO_FILE_FOUND; // exit if file not found
	}

	// read each line of the file
	while (!fin.eof()) {
		// read an entire line into memory
		char buf[MAX_CHARS_PER_LINE];
		// @check too long lines
		fin.getline(buf, MAX_CHARS_PER_LINE);

		if (buf[0] == '\0' || buf[0] == '#') {
			continue;
		}

		char commandName[MAX_CHAR_COMMAND];
		char* token;
		InputType type;
		int value,
			direction = 0;

		// @TODO Check buffer overflow
		token = strtok(buf, DELIMITER);
		strncpy(commandName, token, MAX_CHAR_COMMAND);

		// @TODO check missing values
		token = strtok(0, DELIMITER);
		if (token == 0) {
			return NO_TYPE_FOUND;
		}

		type = (InputType) atoi(token);
		token = strtok(0, DELIMITER);
		if (token == 0) {
			return NO_VALUE_FOUND;
		}

		value = atoi(token);
		token = strtok(0, DELIMITER);

		if (token != 0) {
			direction = atoi(token);
		}

		S_Command c;
		c.type = type;
		switch (type) {
			case KEYBOARD_KEY:
				c.key = (SDL_Scancode) value;
				break;
			case CONTROLLER_BUTTON:
				c.buttonId = (unsigned long) value;
				break;
			case CONTROLLER_STICK:
				c.stickAxis = (JoystickControl) value;
				c.stickDirection = direction;
				break;
			case NULL_TYPE:
				break;
			default:
				return INVALID_TYPE;
		}
		add(commandName, c);
	}

	fin.close();
	return 0;
}
