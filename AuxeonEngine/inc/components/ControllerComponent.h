#pragma once

#ifndef CONTROLLERCOMPONENT_H
#define CONTROLLERCOMPONENT_H

#include "../inc/helpers/Vector2D.h"
#include "../inc/entities/Component.h"
#include "../inc/entities/GameObject.h"
#include "../inc/managers/InputManager.h"

class ControllerComponent : public Component {

public:

	InputManager* ctrlInputManager;
	InputMap ctrlProfile;

	ControllerComponent(int inputProfile = 1);
	~ControllerComponent();

	void comInit();
	void comHandleEvents();
	void comDraw();
	void comUpdate();
};

#endif