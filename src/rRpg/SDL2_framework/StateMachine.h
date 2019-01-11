#ifndef __StateMachine__
#define __StateMachine__

#include "State.h"
#include <vector>

/**
 * Finished state machine. Contains a stack of states.
 * A new state can be pushed on top of the stack, the top state can be changed
 * for another one and the top state can also be popped.
 */
class StateMachine {
	private:
	std::vector<State*> m_vStates = {};

	public:
	void pushState(State* pState);
	void changeState(State* pState);
	bool popState();
	void clean();
	State* getCurrentState();

	/**
	 * Methods to update and render the current state
	 */
	void update();
	void render();
};

#endif
