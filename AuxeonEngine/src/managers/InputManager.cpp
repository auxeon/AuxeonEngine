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
	return ((inmCurrentKeyboardState[keycode]) && !(inmPrevKeyboardState[keycode]));
}

void InputManager::inmUpdate() {
	const Uint8* temp = SDL_GetKeyboardState(&inmKeyCount);
	memcpy(inmPrevKeyboardState, inmCurrentKeyboardState, inmKeyCount*sizeof(Uint8));
	memcpy(inmCurrentKeyboardState, temp, inmKeyCount*sizeof(Uint8));
}

// call the input managers handle event functionality 
void InputManager::inmHandleEvents() {

}

// call the input managers draw functionality 
void InputManager::inmDraw() {

}

InputManager::InputManager() {

	const Uint8* temp = SDL_GetKeyboardState(&inmKeyCount);
	inmCurrentKeyboardState = new Uint8[inmKeyCount];
	inmPrevKeyboardState = new Uint8[inmKeyCount];

	memset(inmCurrentKeyboardState,0,inmKeyCount*sizeof(Uint8));
	memset(inmPrevKeyboardState, 0, inmKeyCount*sizeof(Uint8));

	if (inmPrevKeyboardState) {
		inmInstantiated = inmInit();
	}

	std::cout << "InputManager : default constructed" << std::endl;
}

InputManager::~InputManager() {
	delete[] inmPrevKeyboardState;
	delete[] inmCurrentKeyboardState;
	inmPrevKeyboardState = NULL;
	inmCurrentKeyboardState = NULL;
	std::cout << "InputManager : default destructed" << std::endl;
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

bool InputManager::inmInit() {
	//TO DO load from file later 

	// profile 1 hardcoding for now
	profile1["UP"] = SDL_SCANCODE_W;
	profile1["DOWN"] = SDL_SCANCODE_S;
	profile1["LEFT"] = SDL_SCANCODE_A;
	profile1["RIGHT"] = SDL_SCANCODE_D;
	profile1["ROT_RIGHT"] = SDL_SCANCODE_E;
	profile1["ROT_LEFT"] = SDL_SCANCODE_Q;
	profile1["ROT_BACK"] = SDL_SCANCODE_Z;
	profile1["ROT_FRONT"] = SDL_SCANCODE_C;
	profile1["TEXTURE_TOGGLE"] = SDL_SCANCODE_SPACE;


	// profile 2 hardcoding for now
	profile2["UP"] = SDL_SCANCODE_UP;
	profile2["DOWN"] = SDL_SCANCODE_DOWN;
	profile2["LEFT"] = SDL_SCANCODE_LEFT;
	profile2["RIGHT"] = SDL_SCANCODE_RIGHT;
	profile2["ROT_RIGHT"] = SDL_SCANCODE_P;
	profile2["ROT_LEFT"] = SDL_SCANCODE_I;
	profile2["ROT_BACK"] = SDL_SCANCODE_J;
	profile2["ROT_FRONT"] = SDL_SCANCODE_L;
	profile2["TEXTURE_TOGGLE"] = SDL_SCANCODE_SPACE;

	std::cout << "InputManager : init" << std::endl;

	return true;
}