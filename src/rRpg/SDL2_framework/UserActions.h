#ifndef __UserActions__
#define __UserActions__

#include <string>
#include <map>
#include <vector>
#include "InputHandler.h"

#define NO_FILE_FOUND 1
#define NO_TYPE_FOUND 2
#define NO_VALUE_FOUND 3
#define INVALID_TYPE 4

struct S_Command {
	InputType type = NULL_TYPE;
	unsigned long buttonId = 0;
	int stickDirection = 0;
	JoystickControl stickAxis = NULL_CONTROL;
	SDL_Scancode key = SDL_SCANCODE_INTERNATIONAL1;
};

class UserActions {
	protected:
	std::map<std::string, std::vector<S_Command>> m_mMappings;

	public:
	UserActions();
	void add(std::string name, S_Command c);
	int getActionState(std::string name);
	void resetActionState(std::string name);
	int setActionsFromFile(const char* mappingFile);
};

#endif
