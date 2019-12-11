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
	// keyboard stuff
	const Uint8* temp = SDL_GetKeyboardState(&inmKeyCount);
	memcpy(inmPrevKeyboardState, inmCurrentKeyboardState, inmKeyCount * sizeof(Uint8));
	memcpy(inmCurrentKeyboardState, temp, inmKeyCount * sizeof(Uint8));

	// 
}

// call the input managers handle event functionality 
void InputManager::inmHandleEvents() {

}

// call the input managers draw functionality 
void InputManager::inmDraw() {

}

InputManager::InputManager() : inmMouseDX(0.0f), inmMouseDY(0.0f) {

	// keyboard stuff 
	const Uint8* temp = SDL_GetKeyboardState(&inmKeyCount);
	inmCurrentKeyboardState = new Uint8[inmKeyCount];
	inmPrevKeyboardState = new Uint8[inmKeyCount];

	memset(inmCurrentKeyboardState, 0, inmKeyCount * sizeof(Uint8));
	memset(inmPrevKeyboardState, 0, inmKeyCount * sizeof(Uint8));

	if (inmPrevKeyboardState) {
		inmInstantiated = inmInit();
	}
	// mouse stuff
	inmMousePosition = new vec2(0.0f, 0.0f);

	//reset all states
	for (int i = 0; i < 3; i++) {
		inmMouseButtonStates.push_back(false);
	}

	std::cout << "InputManager : default constructed" << std::endl;
}

InputManager::~InputManager() {
	delete[] inmPrevKeyboardState;
	delete[] inmCurrentKeyboardState;
	delete inmMousePosition;
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

	// profile
	profile1["UP"] = SDL_SCANCODE_W;
	profile1["DOWN"] = SDL_SCANCODE_S;
	profile1["RUN_LEFT"] = SDL_SCANCODE_A;
	profile1["RUN_RIGHT"] = SDL_SCANCODE_D;
	profile1["ROT_RIGHT"] = SDL_SCANCODE_E;
	profile1["ROT_LEFT"] = SDL_SCANCODE_Q;
	profile1["JUMP"] = SDL_SCANCODE_SPACE;
	profile1["PUNCH"] = SDL_SCANCODE_Z;
	profile1["KICK"] = SDL_SCANCODE_C;
	profile1["TEXTURE_TOGGLE"] = SDL_SCANCODE_T;


	// profile 2
	profile2["UP"] = SDL_SCANCODE_UP;
	profile2["DOWN"] = SDL_SCANCODE_DOWN;
	profile2["RUN_LEFT"] = SDL_SCANCODE_LEFT;
	profile2["RUN_RIGHT"] = SDL_SCANCODE_RIGHT;
	profile2["ROT_RIGHT"] = SDL_SCANCODE_P;
	profile2["ROT_LEFT"] = SDL_SCANCODE_I;
	profile2["JUMP"] = SDL_SCANCODE_J;
	profile2["PUNCH"] = SDL_SCANCODE_J;
	profile2["KICK"] = SDL_SCANCODE_L;
	profile2["TEXTURE_TOGGLE"] = SDL_SCANCODE_Y;

	std::cout << "InputManager : init" << std::endl;

	return true;
}

// Input management for mouse stuff 
void InputManager::inmMouseButtonDown(SDL_Event& event) {
	if (event.button.button == SDL_BUTTON_LEFT) {
		inmMouseButtonStates[LB] = true;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE) {
		inmMouseButtonStates[MB] = true;
	}
	if (event.button.button == SDL_BUTTON_RIGHT) {
		inmMouseButtonStates[RB] = true;
	}
}

bool InputManager::inmMouseMove(SDL_Event& event) {

	if (event.type == SDL_MOUSEMOTION) {
		inmMouseDX = event.motion.x - inmMousePosition->x;
		inmMouseDY = event.motion.y - inmMousePosition->y;

		inmMousePosition->x = (event.motion.x);
		inmMousePosition->y = (event.motion.y);

		if (inmMouseDX != 0.0f || inmMouseDY != 0.0f) {
			return true;
		}
	}
	return false;
}

void InputManager::inmMouseButtonUp(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT) {
		inmMouseButtonStates[LB] = false;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE) {
		inmMouseButtonStates[MB] = false;
	}
	if (event.button.button == SDL_BUTTON_RIGHT) {
		inmMouseButtonStates[RB] = false;
	}
}

bool InputManager::inmGetMouseButtonState(int buttonNumber) {
	return inmMouseButtonStates[buttonNumber];
}

vec2* InputManager::inmGetMousePosition() {
	return inmMousePosition;
}