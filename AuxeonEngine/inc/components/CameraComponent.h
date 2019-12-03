#pragma once

#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

// helpers
#include "../inc/helpers/shader.h"
#include "../libs/GLM-0.9.9.6/glm/glm.hpp"

// entities
#include "../inc/entities/Component.h"
#include "../inc/entities/GameObject.h"

// managers
#include "../inc/managers/GraphicsManager.h"
#include "../inc/managers/InputManager.h"
#include "../inc/managers/FrameRateManager.h"

using vec3 = glm::vec3;
using mat4 = glm::mat4;
using float32 = glm::float32;


class CameraComponent : public Component
{
public:
	// vectors
	vec3 camPos;
	vec3 camTarget;
	vec3 camDirection;
	vec3 camUp;
	vec3 camRight;

	// matrices
	mat4 camLookAt;
	
	// floats
	float32 camPitch; // xrot
	float32 camYaw;   // yaw
	float32 camRoll;  // roll
	float32 camFOV;
	float32 camNearClip;
	float32 camFarClip;


public:	
	CameraComponent();
	~CameraComponent();
	void comInit();
	void comUpdate();
	void comHandleEvents();
	void comDraw();

};

#endif 
