#include "../inc/managers/GraphicsManager.h"


GraphicsManager* GraphicsManager::gfxInstance = NULL;
bool GraphicsManager::gfxInstantiated = false;

GraphicsManager* GraphicsManager::gfxCreate() {
	if (NULL == gfxInstance) {
		gfxInstance = new GraphicsManager();
	}
	return(gfxInstance);
}

void GraphicsManager::gfxDestroy() {
	delete gfxInstance;
	gfxInstance = NULL;
	gfxInstantiated = false;
}

bool GraphicsManager::gfxGetInstantiated() {
	return(gfxInstantiated);
}

GraphicsManager::GraphicsManager() {
	gfxWindowSurface = NULL;
	gfxInstantiated = gfxInit();
}

GraphicsManager::~GraphicsManager() {
	SDL_DestroyWindow(gfxWindow);
	gfxWindow = NULL;
	SDL_Quit();
}

void GraphicsManager::gfxSetWindowTitle(const char* title) {
	if (NULL != gfxWindow) {
		SDL_SetWindowTitle(gfxWindow, title);
	}
}

bool GraphicsManager::gfxInit() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL Init errror : " << SDL_GetError() << std::endl;
	}

	gfxWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gfxScreenWidth, gfxScreenHeight, SDL_WINDOW_SHOWN);


	if (NULL == gfxWindow) {
		std::cout << "Error creating window : " << SDL_GetError() << std::endl;
		return(false);
	}

	gfxWindowSurface = SDL_GetWindowSurface(gfxWindow);
	
	return(true);
}

SDL_Surface* GraphicsManager::gfxGetWindowSurface() {
	return(gfxWindowSurface);
}

void GraphicsManager::gfxDraw() {
	SDL_FillRect(gfxWindowSurface, NULL, 0x000000);
}

// call the graphics managers handle event functionality 
void GraphicsManager::gfxHandleEvents() {

}

// call the graphics managers update functionality 
void GraphicsManager::gfxUpdate() {
	SDL_UpdateWindowSurface(gfxWindow);
}