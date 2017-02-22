#ifndef __PLAY_STATE__
#define __PLAY_STATE__

#include "SDL2_framework/GameState.h"

class PlayState : public GameState {
	private:
	static const std::string s_stateID;

	public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const;
};

#endif
