#pragma once

#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#include "../../SDL2-2.0.10/include/SDL.h"

#include <iostream>

class GraphicsManager {

	// data
public:
	static const int gfxScreenWidth = SCREEN_WIDTH;
	static const int gfxScreenHeight = SCREEN_HEIGHT;

private:
	static GraphicsManager* gfxInstance;
	static bool gfxInstantiated;
	SDL_Window* gfxWindow;
	SDL_Surface* gfxWindowSurface;

	// functions
public:
	static GraphicsManager* gfxCreate();
	static bool gfxGetInstantiated();
	static void gfxDestroy();

	SDL_Surface* gfxGetWindowSurface();
	void gfxSetWindowTitle(const char* title);
	void gfxDraw();
	void gfxUpdate();
	void gfxHandleEvents();

private:
	GraphicsManager();
	~GraphicsManager();
	bool gfxInit();
};


#endif /* Graphics_hpp */