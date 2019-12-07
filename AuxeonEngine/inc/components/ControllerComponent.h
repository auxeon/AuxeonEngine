#pragma once

#ifndef CONTROLLERCOMPONENT_H
#define CONTROLLERCOMPONENT_H
// helpers
#include "../libs/GLM-0.9.9.6/glm/gtx/transform.hpp"
// entities
#include "../inc/entities/Component.h"
#include "../inc/entities/GameObject.h"
// inputmanager
#include "../inc/managers/InputManager.h"
#include "../inc/managers/FrameRateManager.h"
// components
#include "../inc/components/TransformComponent.h"
#include "../inc/components/ModelComponent.h"
#include "../inc/components/Model3DComponent.h"

class ControllerComponent : public Component {

public:

	InputManager* ctrlInputManager;
	FrameRateManager* ctrlFrameRateManager;
	InputMap ctrlProfile;

	ControllerComponent(int inputProfile = 1);
	~ControllerComponent();

	void comInit();
	void comHandleEvents();
	void comDraw();
	void comUpdate();
};

#endif