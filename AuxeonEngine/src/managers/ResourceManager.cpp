#include "../inc/managers/ResourceManager.h"
#include <iostream>

ResourceManager* ResourceManager::resInstance = NULL;
bool ResourceManager::resInstantiated = false;

ResourceManager* ResourceManager::resCreate() {
	if (NULL == resInstance) {
		resInstance = new ResourceManager();
	}
	return(resInstance);
}

void ResourceManager::resDestroy() {
	delete resInstance;
	resInstance = NULL;
}

SDL_Surface* ResourceManager::resLoadSurface(const char* filePath) {
	if (!resSurfaces[filePath]) {
		resSurfaces[filePath] = SDL_LoadBMP(filePath);
	}
	return(resSurfaces[filePath]);
}

bool ResourceManager::resGetInstantiated() {
	return(resInstantiated);
}

ResourceManager::ResourceManager() {
	resInstantiated = resInit();
	std::cout << "ResourceManager : default constructed" << std::endl;
}

ResourceManager::~ResourceManager() {
	for (auto surf : resSurfaces) {
		if (surf.second) {
			SDL_FreeSurface(surf.second);
		}
	}
	std::cout << "ResourceManager : default destructed" << std::endl;
}


void ResourceManager::resUpdate() {

}

void ResourceManager::resDraw() {

}

void ResourceManager::resHandleEvents() {

}

bool ResourceManager::resInit() {
	std::cout << "ResourceManager : init" << std::endl;
	return true;
}