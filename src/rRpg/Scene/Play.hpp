#ifndef __PLAY_STATE__
#define __PLAY_STATE__

#include "SDL2_framework/State.h"
#include "rRpg.hpp"

class PlayScene : public State {
	private:
	static const std::string s_stateID;
	rRpg engine;

	public:
	PlayScene();
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const;
};

#endif
