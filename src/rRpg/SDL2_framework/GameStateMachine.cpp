#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState *pState) {
	// if the current state is the same as the pushed one, do nothing
	if (!m_vGameStates.empty() && m_vGameStates.back()->getStateID() == pState->getStateID()) {
		return;
	}

	m_vGameStates.push_back(pState);
	if (!m_vGameStates.back()->onEnter()) {
		popState();
	}
}

void GameStateMachine::changeState(GameState *pState) {
	// If there is at least one state
	if (!m_vGameStates.empty()) {
		// and if it is the state we want to add
		if (m_vGameStates.back()->getStateID() == pState->getStateID()) {
			return;
		}

		// remove the state
		popState();
	}

	// add the new one
	pushState(pState);
}

bool GameStateMachine::popState() {
	if (!m_vGameStates.empty() && m_vGameStates.back()->onExit()) {
		delete m_vGameStates.back();
		m_vGameStates.pop_back();
		return true;
	}

	return false;
}

void GameStateMachine::clean() {
	while (popState()) {}
}

GameState* GameStateMachine::getCurrentState() {
	return m_vGameStates.back();
}

void GameStateMachine::update() {
	if (!m_vGameStates.empty()) {
		m_vGameStates.back()->update();
	}
}
void GameStateMachine::render() {
	if (!m_vGameStates.empty()) {
		m_vGameStates.back()->render();
	}
}
