#pragma once

#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

// helpers
#include "../inc/helpers/Vector2D.h"
// entities
#include "../inc/entities/Component.h"
#include "../inc/entities/GameObject.h"
// managers
#include "../inc/managers/GraphicsManager.h"
#include "../inc/managers/ResourceManager.h"

using String = std::string;

class SpriteComponent : public Component {

public:

	GraphicsManager* sprGraphicsManager;
	ResourceManager* sprResourceManager;

	SDL_Surface* sprSurface;
	SDL_Rect* sprRect;
	String sprPath;

	int sprWidth;
	int sprHeight;

	SpriteComponent(String path="../res/sprites/default.bmp");
	~SpriteComponent();

	void comInit();
	void comHandleEvents();
	void comDraw();
	void comUpdate();
};

#endif