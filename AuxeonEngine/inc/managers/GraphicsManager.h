#pragma once

#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#include "../libs/SDL2-2.0.10/include/SDL.h"
#include "../libs/GLAD-OPENGL-4.6/glad/include/glad/glad.h"
#include "../libs/GLM-0.9.9.6/glm/glm.hpp"

#include "../inc/entities/GameObject.h"
#include "../inc/entities/Component.h"

#include <iostream>

using GameObjectMap = std::unordered_map<int, GameObject*>;
using GameObjectIDPair = std::pair<int, GameObject*>;
using vec4 = glm::vec4;
using vec3 = glm::vec3;

class GraphicsManager {

	// data
public:
	static const int gfxScreenWidth = SCREEN_WIDTH;
	static const int gfxScreenHeight = SCREEN_HEIGHT;
	bool gfxDebugDraw;
	vec3 gfxDebugDrawColor;
	static GameObject* gfxActiveCamera;

	//OpenGL
	SDL_GLContext gfxOpenGLContext;

private:
	static GraphicsManager* gfxInstance;
	static bool gfxInstantiated;
	SDL_Window* gfxWindow;
	SDL_Surface* gfxWindowSurface;
	GameObjectMap gfxCamMap;



	// functions
public:
	static GraphicsManager* gfxCreate();
	static bool gfxGetInstantiated();
	static void gfxDestroy();

	SDL_Surface* gfxGetWindowSurface();
	SDL_Window* gfxGetWindow();
	void gfxSetWindowTitle(const char* title);
	void gfxDraw();
	void gfxUpdate();
	void gfxHandleEvents();

	void gfxAddCam(GameObjectIDPair cam);
	void gfxRemoveCam(GameObjectIDPair cam);

private:
	GraphicsManager();
	~GraphicsManager();
	bool gfxInit();
};


#endif /* Graphics_hpp */