#ifndef __GameStateMachine__
#define __GameStateMachine__

#include "GameState.h"
#include <vector>

/**
 * Finished state machine. Contains a stack of states.
 * A new state can be pushed on top of the stack, the top state can be changed
 * for another one and the top state can also be popped.
 */
class GameStateMachine {
	private:
	std::vector<GameState*> m_vGameStates = {};

	public:
	void pushState(GameState* pState);
	void changeState(GameState* pState);
	bool popState();
	void clean();
	GameState* getCurrentState();

	/**
	 * Methods to update and render the current state
	 */
	void update();
	void render();
};

#endif
