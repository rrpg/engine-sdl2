#ifndef __GAME_OVER_STATE__
#define __GAME_OVER_STATE__

#include "SDL2_framework/GameState.h"

class GameOverState : public GameState {
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
