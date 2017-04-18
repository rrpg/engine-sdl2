#ifndef __NoJoystickState__
#define __NoJoystickState__

#include "GameState.h"

/**
 * State used when a joystick is unplugged
 */
class NoJoystickState : public GameState {
	private:
	static const std::string s_menuID;

	public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const;
};

#endif

