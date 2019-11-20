#include "../inc/components/SpriteComponent.h"


SpriteComponent::SpriteComponent(String path) : sprPath(path), sprWidth(100), sprHeight(100){
	sprGraphicsManager = GraphicsManager::gfxCreate();
	sprResourceManager = ResourceManager::resCreate();
	sprSurface = new SDL_Surface;
	sprRect = new SDL_Rect;
}

SpriteComponent::~SpriteComponent() {
	delete sprSurface;
	delete sprRect;
}

void SpriteComponent::comInit() {

	sprSurface = sprResourceManager->resLoadSurface(sprPath.c_str());
	if (comOwner->gaxComponentExists<TransformComponent>()) {
		sprRect->w = sprWidth;
		sprRect->h = sprHeight;
		sprRect->x = comOwner->gaxGetComponent<TransformComponent>().txfPosition.x;
		sprRect->y = comOwner->gaxGetComponent<TransformComponent>().txfPosition.y;
	}
}

void SpriteComponent::comUpdate() {
	sprRect->x = comOwner->gaxGetComponent<TransformComponent>().txfPosition.x;
	sprRect->y = comOwner->gaxGetComponent<TransformComponent>().txfPosition.y;
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