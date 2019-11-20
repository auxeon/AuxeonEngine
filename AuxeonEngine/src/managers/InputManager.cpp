#include "../inc/managers/InputManager.h"

InputManager* InputManager::inmInstance = NULL;
bool InputManager::inmInstantiated = false;

bool InputManager::inmGetExists() {
	return(inmGetInstantiated());
}

InputManager* InputManager::inmCreate() {
	if (NULL == inmInstance) {
		inmInstance = new InputManager();
	}
	return(inmInstance);
}

void InputManager::inmDestroy() {
	delete inmInstance;
	inmInstance = NULL;
	inmInstantiated = false;
}

bool InputManager::inmIsKeyPressed(SDL_Scancode keycode) {
	return(inmCurrentKeyboardState[keycode]);
}

bool InputManager::inmIsKeyReleased(SDL_Scancode keycode) {
	return(!inmCurrentKeyboardState[keycode] && inmPrevKeyboardState[keycode]);
}

bool InputManager::inmIsKeyTriggered(SDL_Scancode keycode) {
	return (inmCurrentKeyboardState[keycode] && !inmPrevKeyboardState[keycode]);
}

void InputManager::inmUpdate() {
	memcpy(inmPrevKeyboardState, inmCurrentKeyboardState, inmKeyCount);
}

// call the input managers handle event functionality 
void InputManager::inmHandleEvents() {

}

// call the input managers draw functionality 
void InputManager::inmDraw() {

}

InputManager::InputManager() {
	inmCurrentKeyboardState = SDL_GetKeyboardState(&inmKeyCount);
	inmPrevKeyboardState = new Uint8[inmKeyCount];
	memcpy(inmPrevKeyboardState, inmCurrentKeyboardState, inmKeyCount);
	if (inmPrevKeyboardState) {
		inmInstantiated = true;
	}


	//TO DO load from file later 

	// profile 1 hardcoding for now
	profile1["UP"] = SDL_SCANCODE_W;
	profile1["DOWN"] = SDL_SCANCODE_S;
	profile1["LEFT"] = SDL_SCANCODE_A;
	profile1["RIGHT"] = SDL_SCANCODE_D;
	

	// profile 2 hardcoding for now
	profile2["UP"] = SDL_SCANCODE_UP;
	profile2["DOWN"] = SDL_SCANCODE_DOWN;
	profile2["LEFT"] = SDL_SCANCODE_LEFT;
	profile2["RIGHT"] = SDL_SCANCODE_RIGHT;


}

InputManager::~InputManager() {
	delete[] inmPrevKeyboardState;
	inmPrevKeyboardState = NULL;
}

bool InputManager::inmGetInstantiated() {
	return(inmInstantiated);
}


InputMap InputManager::inmGetProfile(int choice) {
	int flag = 1;
	switch (choice) {
	case 1:
		flag = 1;
		break;
	case 2:
		flag = 2;
		break;
	default:
		break;

	}
	if (1 == flag)
		return profile1;
	if (2 == flag)
		return profile2;
}