#pragma once

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "../inc/helpers/Vector2D.h"
#include "../inc/entities/Component.h"
#include "../inc/entities/GameObject.h"

class TransformComponent : public Component{

public:
	// objects orientation in 2D space
	Vector2D txfPosition;
	Vector2D txfUpVec;
	Vector2D txfRightVec;
	Vector2D txfVelocity;
	float txfMaxSpeed;
	
public:
	TransformComponent();
	TransformComponent(float x , float y, float max_speed);
	~TransformComponent();
	void comInit();
	void comHandleEvents();
	void comDraw();
	void comUpdate();


};

#endif