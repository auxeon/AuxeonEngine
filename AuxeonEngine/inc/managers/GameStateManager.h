#pragma once

#ifndef GSM_H
#define GSM_H

#include <vector>

class State;
class GameStateManager
{
//static
public:
	static GameStateManager* gsmCreate();
	static void gsmDestroy();
	static bool gsmGetInstantiated();
	
private:
	static bool gsmInstantiated;
	static bool gsmRunning;
	static GameStateManager* gsmInstance;

// data
public:
	enum gsmStateList {MAIN_MENU,
		LOADING,
		LEVEL_1,
		LEVEL_2,
		LEVEL_3,
		RESTART,
		QUIT};
	
// functions
public:

	bool gsmCleanup();

	bool gsmIsRunning() { return gsmRunning; };
	bool gsmQuit() { gsmRunning = false; return(gsmRunning); };

	void gsmChangeState(State* state);
	void gsmPushState(State* state);
	void gsmPopState();

	void gsmHandleEvents();
	void gsmDraw();
	void gsmUpdate();

// data
private:
	
	State* gsmCurrState;
	State* gsmPrevState;
	// store the stateId and the state pointers 
	std::vector<State*> gsmStates;

// functions
private:
	GameStateManager();
	~GameStateManager();
	bool gsmInit();
};

// do not instantiate the static members inside the .h file otherwise you get LNK2005 
// this is because each file that calls this header file redefines the static members
// instead put it in the .cpp file 
//bool GameStateManager::gsmInstantiated = false;
//GameStateManager* GameStateManager::gsmInstance = NULL;

#endif