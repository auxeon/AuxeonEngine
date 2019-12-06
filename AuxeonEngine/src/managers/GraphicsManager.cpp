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
	std::cout << "GraphicsManager : default constructed" << std::endl;
}

GraphicsManager::~GraphicsManager() {
	SDL_DestroyWindow(gfxWindow);
	gfxWindow = NULL;
	SDL_Quit();
	std::cout << "GraphicsManager : default destructed" << std::endl;
}

void GraphicsManager::gfxSetWindowTitle(const char* title) {
	if (NULL != gfxWindow) {
		SDL_SetWindowTitle(gfxWindow, title);
	}
}

bool GraphicsManager::gfxInit() {

	// initialize sdl with the video subsystem initialization flags
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL Init errror : " << SDL_GetError() << std::endl;
	}

	// creating the window to render to with the necessary flags
	gfxWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gfxScreenWidth, gfxScreenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (NULL == gfxWindow) {
		std::cout << "Error creating window : " << SDL_GetError() << std::endl;
		return(false);
	}

	// set opengl version flags
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,6);

	// setting the core profile doesn't allow us to use older deprecated functions 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


	// creating the main sdl opengl context now
	gfxOpenGLContext = SDL_GL_CreateContext(gfxWindow);

	gfxWindowSurface = SDL_GetWindowSurface(gfxWindow);

	// use glad loader to gain access to openGL calls - needed on windows only 
	#ifdef _WIN32
	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
	#endif

	// let's print out the OpenGL version info 
	std::cout <<"GraphicsManager : gfxInit : OpenGL Version "<< (char*)glGetString(GL_VERSION)<<std::endl;

	return(true);
}

SDL_Surface* GraphicsManager::gfxGetWindowSurface() {
	return(gfxWindowSurface);
}

SDL_Window* GraphicsManager::gfxGetWindow() {
	return(gfxWindow);
}

void GraphicsManager::gfxDraw() {
	SDL_GL_SwapWindow(gfxWindow);
}

// call the graphics managers handle event functionality 
void GraphicsManager::gfxHandleEvents() {

}

// call the graphics managers update functionality 
void GraphicsManager::gfxUpdate() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsManager::gfxAddCam(GameObjectIDPair cam) {
	gfxCamMap.insert(cam);
	std::cout << "GraphicsManager : Camera inserted : " << cam.first << std::endl;
}

void GraphicsManager::gfxRemoveCam(GameObjectIDPair cam) {
	gfxCamMap.erase(cam.first);
	std::cout << "GraphicsManager : Camera deleted : " << cam.first << std::endl;
}