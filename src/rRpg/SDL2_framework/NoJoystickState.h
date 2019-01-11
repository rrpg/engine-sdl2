#ifndef __NoJoystickState__
#define __NoJoystickState__

#include "State.h"

/**
 * State used when a joystick is unplugged
 */
class NoJoystickState : public State {
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

