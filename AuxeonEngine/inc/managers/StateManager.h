#pragma once

#ifndef STATE_H
#define STATE_H

#include "../inc/managers/GameStateManager.h"

class State
{
public:
	virtual void stateInit() = 0;
	virtual void stateCleanup() = 0;
	virtual void statePause() = 0;
	virtual void stateResume() = 0;
	virtual void stateHandleEvents() = 0;
	virtual void stateUpdate() = 0;
	virtual void stateDraw() = 0;
	virtual bool stateGetExists() = 0;
	

	void stateChangeState(GameStateManager* gameState, State* state) {
		gameState->gsmChangeState(state);
	}

};

#endif