#include "../inc/components/SpriteComponent.h"

// include this only in the c++ file and add it just once with an IFNDEF otherwise it leads to multiple includes/
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "../inc/helpers/stb_image.h"
#endif

SpriteComponent::SpriteComponent(String path, int w, int h) : sprPath(path), sprWidth(w), sprHeight(h){
	sprGraphicsManager = GraphicsManager::gfxCreate();
	sprResourceManager = ResourceManager::resCreate();
	sprSurface = new SDL_Surface;
	sprRect = new SDL_Rect;
}

SpriteComponent::~SpriteComponent() {
	delete sprSurface;
	delete sprRect;

}

// comOwner is available from here on
void SpriteComponent::comInit() {

	sprSurface = sprResourceManager->resLoadSurface(sprPath.c_str());
	if (comOwner->gaxComponentExists<TransformComponent>()) {
		sprRect->w = sprWidth;
		sprRect->h = sprHeight;

	}


}

void SpriteComponent::comUpdate() {
	sprRect->x = comOwner->gaxGetComponent<TransformComponent>().txfPosition.x;
	sprRect->y = comOwner->gaxGetComponent<TransformComponent>().txfPosition.y;

	SDL_UpdateWindowSurface(sprGraphicsManager->gfxGetWindow());
}

void SpriteComponent::comDraw() {


	if (comOwner->gaxComponentExists<TransformComponent>()) {
		SDL_BlitSurface(sprSurface, NULL, sprGraphicsManager->gfxGetWindowSurface(), sprRect);
	}
	else {
		std::cout << "SpriteComponent : parent object has no TransformComponent\n";
	}
}

void SpriteComponent::comHandleEvents() {

}