#pragma once

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <iostream>
#include <cstring>
#include <unordered_map>
#include <vector>
// SDL
#include "../libs/SDL2-2.0.10/include/SDL.h"
// helpers
// helpers
#define GLM_SWIZZLE_XYZW
#include "../libs/GLM-0.9.9.6/glm/glm.hpp"
#include "../libs/GLM-0.9.9.6/glm/gtx/transform.hpp"

enum inmMouseButtons {
	LB = 0,
	MB = 1,
	RB = 2
};

using InputMap = std::unordered_map<std::string, SDL_Scancode>;
using vec2 = glm::vec2;
using float32 = glm::float32;
using vecbool = std::vector<bool>;

class InputManager {

public:
	float32 inmMouseDX;
	float32 inmMouseDY;

private:
	static InputManager* inmInstance;
	static bool inmInstantiated;

	// keyboard stuff
	Uint8* inmCurrentKeyboardState;
	Uint8* inmPrevKeyboardState;

	int inmKeyCount;
	InputMap profile1;
	InputMap profile2;

	// mouse stuff
	vecbool inmMouseButtonStates;
	vec2* inmMousePosition;


public:

	static InputManager* inmCreate();
	static void inmDestroy();
	static bool inmGetInstantiated();
	bool inmGetExists();

	// keyboard stuff
	bool inmIsKeyPressed(SDL_Scancode);
	bool inmIsKeyReleased(SDL_Scancode);
	bool inmIsKeyTriggered(SDL_Scancode);

	//mouse stuff
	void inmMouseButtonDown(SDL_Event& event);
	bool inmMouseMove(SDL_Event& event);
	void inmMouseButtonUp(SDL_Event& event);
	bool inmGetMouseButtonState(int buttonNumber);
	vec2* inmGetMousePosition();

	void inmUpdate();
	void inmDraw();
	void inmHandleEvents();

	InputMap inmGetProfile(int);

private:
	InputManager();
	~InputManager();
	bool inmInit();

};

#endif

