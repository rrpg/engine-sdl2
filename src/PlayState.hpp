#ifndef __PLAY_STATE__
#define __PLAY_STATE__

#include "SDL2_framework/GameState.h"
#include "rRpg.hpp"

class PlayState : public GameState {
	private:
	static const std::string s_stateID;
	uint32_t m_iTimestampLastCommand = 0;
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
