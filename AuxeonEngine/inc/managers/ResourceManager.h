#pragma once
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <unordered_map>
#include "../libs/SDL2-2.0.10/include/SDL.h"


using ResourceMap = std::unordered_map<const char*, SDL_Surface*>;

class ResourceManager {

private:
	static ResourceManager* resInstance;
	static bool resInstantiated;
	ResourceMap resSurfaces;

public:
	static ResourceManager* resCreate();
	static bool resGetInstantiated();
	static void resDestroy();

	void resUpdate();
	void resDraw();
	void resHandleEvents();

	SDL_Surface* resLoadSurface(const char* filePath);

private:
	ResourceManager();
	~ResourceManager();
	bool resInit();
};


#endif
