#pragma once

// is kinda broken right now 


#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H
// helpers
#include "../inc/helpers/shader.h"
#include "../inc/helpers/Vector2D.h"
// entities
#include "../inc/entities/Component.h"
#include "../inc/entities/GameObject.h"
// managers
#include "../inc/managers/GraphicsManager.h"
#include "../inc/managers/ResourceManager.h"
// components
#include "../inc/components/TransformComponent.h"

using String = std::string;

class SpriteComponent : public Component {

public:

	GraphicsManager* sprGraphicsManager;
	ResourceManager* sprResourceManager;

	SDL_Surface* sprSurface;
	SDL_Rect* sprRect;
	String sprPath;

	Vector2D sprPos;
	int sprWidth;
	int sprHeight;

	SpriteComponent(String path="../res/sprites/default.bmp",int w=10, int h=10);	
	~SpriteComponent();

	void comInit();
	void comHandleEvents();
	void comDraw();
	void comUpdate();
};

#endif