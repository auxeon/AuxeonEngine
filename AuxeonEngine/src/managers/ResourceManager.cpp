#include "../inc/managers/ResourceManager.h"

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
	resInstantiated = true;
}

ResourceManager::~ResourceManager() {
	for (auto surf : resSurfaces) {
		if (surf.second) {
			SDL_FreeSurface(surf.second);
		}
	}
}


void ResourceManager::resUpdate() {

}

void ResourceManager::resDraw() {

}

void ResourceManager::resHandleEvents() {

}