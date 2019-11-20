#include "../inc/managers/GameStateManager.h"
#include "../inc/managers/StateManager.h"
#include <iostream>

// defining the static stuff 
bool GameStateManager::gsmInstantiated = false;
bool GameStateManager::gsmRunning = false;
GameStateManager* GameStateManager::gsmInstance = NULL;

bool GameStateManager::gsmInit() {
	std::cout << "GameStateManager : init\n";
	return(true);
}

bool GameStateManager::gsmCleanup() {
	std::cout << "GameStateManager : cleanup\n";
	fflush(stdout);
	gsmDestroy();
	return(true);
}

// To create the gamestatemanagerinstance
GameStateManager* GameStateManager::gsmCreate() {
	if (!gsmInstantiated) {
		gsmInstance = new GameStateManager();
		if (NULL != gsmInstance) {
			gsmInstantiated = true;
			gsmRunning = true;
		}
	}
	return(gsmInstance);
}

// To destroy the game state manager
void GameStateManager::gsmDestroy() {

	if (gsmInstantiated) {
		delete gsmInstance;
		gsmInstance = NULL;
		gsmInstantiated = false;
		gsmRunning = false;
	}
}
// To get the current DOA status of the class
bool GameStateManager::gsmGetInstantiated() {
	return gsmInstantiated;
}

// Default constructor
GameStateManager::GameStateManager() : gsmCurrState(NULL), gsmPrevState(NULL){
	std::cout << "GameStateManager : default constructed\n";
}

// Default destructor implementation
GameStateManager::~GameStateManager() {

	while (!gsmStates.empty()) {
		gsmPrevState = gsmCurrState;
		if (gsmPrevState->stateGetExists()) {
			gsmPrevState->stateCleanup();
		}
		gsmStates.pop_back();
		if (!gsmStates.empty()) {
			gsmCurrState = gsmStates.back();
		}
	}
	std::cout << "GameStateManager : default destructed\n";

}
// Popping out the latest state from the stack
void GameStateManager::gsmPopState() {

	// cleanup the current last state pop it
	if (!gsmStates.empty()) {
		gsmPrevState = gsmStates.back();
		gsmPrevState->stateCleanup();
		gsmStates.pop_back();
	}

	// set the new last state as the current one then resume the state
	if (!gsmStates.empty()) {
		gsmCurrState = gsmStates.back();
		gsmCurrState->stateResume();
	}


}

// Swapping the current state without adding any new state.
void GameStateManager::gsmChangeState(State* state) {
	
	// cleanup the current State
	if (NULL != gsmCurrState) {
		gsmCurrState->stateCleanup();
	}
	// make prev = curr, curr = state
	gsmPrevState = gsmCurrState;
	gsmCurrState = state;

	// pop the state off the top
	if (!gsmStates.empty()) {
		gsmStates.pop_back();
	}
	// push the new state on the stack and initialize it	
	gsmStates.push_back(state);
	gsmCurrState->stateInit();
	
}

// Adding the latest state to the stack
void GameStateManager::gsmPushState(State* state) {
	gsmStates.push_back(state);
	if (NULL == gsmCurrState) {
		gsmPrevState = gsmCurrState = state;
	}
	else {
		gsmPrevState = gsmCurrState;
		gsmCurrState = state;
	}
}

// call the current states draw functionality 
void GameStateManager::gsmDraw() {
	gsmCurrState->stateDraw();
}

// call the current states handle event functionality 
void GameStateManager::gsmHandleEvents() {
	gsmCurrState->stateHandleEvents();
}

// call the current states update functionality 
void GameStateManager::gsmUpdate() {
	gsmCurrState->stateUpdate();
}



