// AuxeonEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.

#define SDL_MAIN_HANDLED

#include <iostream>
//#include "inc/managers/GameStateManager.h"
#include "inc/states/Level001.h"

FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}
#pragma comment(lib, "legacy_stdio_definitions.lib")

int main()
{

	// create the main game object 
	GameStateManager* game = GameStateManager::gsmCreate();
	
	// load the 1st level
	game->gsmChangeState(Level001::stateCreate(game));

	// game loop
	while (game->gsmIsRunning()) {
		game->gsmHandleEvents();
		game->gsmUpdate();
		game->gsmDraw();
	}
	
	// cleanup and destroy the main game object 
	game->gsmCleanup();
	return(0);
}
