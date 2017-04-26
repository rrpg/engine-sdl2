#ifndef __PLAY_STATE__
#define __PLAY_STATE__

#include "SDL2_framework/GameState.h"
#include "../rRpg.hpp"

class PlayState : public GameState {
	private:
	static const std::string s_stateID;
	rRpg engine;

	public:
	PlayState();
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const;
};

#endif
