#pragma once

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <iostream>
#include <cstring>
#include <unordered_map>
#include "../../SDL2-2.0.10/include/SDL.h"

using InputMap = std::unordered_map<std::string,SDL_Scancode>;




class InputManager {

private:
	static InputManager* inmInstance;
	static bool inmInstantiated;

	const Uint8* inmCurrentKeyboardState;
	Uint8* inmPrevKeyboardState;
	int inmKeyCount;
	InputMap profile1;
	InputMap profile2;

public:

	static InputManager* inmCreate();
	static void inmDestroy();
	static bool inmGetInstantiated();
	bool inmGetExists();

	bool inmIsKeyPressed(SDL_Scancode);
	bool inmIsKeyReleased(SDL_Scancode);
	bool inmIsKeyTriggered(SDL_Scancode);

	void inmUpdate();
	void inmDraw();
	void inmHandleEvents();

	InputMap inmGetProfile(int);

private:
	InputManager();
	~InputManager();

};

#endif

