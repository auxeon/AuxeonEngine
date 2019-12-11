#pragma once

#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum CameraMovement {
	CAMFORWARD,
	CAMBACKWARD,
	CAMLEFT,
	CAMRIGHT
};

// Default camera values
const float CAMYAW = -90.0f;
const float CAMPITCH = 0.0f;
const float CAMSPEED = 2.5f;
const float CAMSENSITIVITY = 0.1f;
const float CAMZOOM = 90.0f;

// helpers
#define GLM_SWIZZLE_XYZW
#include "../libs/GLM-0.9.9.6/glm/glm.hpp"
#include "../libs/GLM-0.9.9.6/glm/gtx/transform.hpp"
#include "../inc/helpers/shader.h"


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
	// Camera Attributes
	vec3 camPosition;
	vec3 camFront;
	vec3 camUp;
	vec3 camRight;
	vec3 camWorldUp;
	// Euler Angles
	float camYaw;
	float camPitch;
	// Camera options
	float camMovementSpeed;
	float camMouseSensitivity;
	float camZoom;

public:
	CameraComponent(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), float yaw = CAMYAW, float pitch = CAMPITCH);
	CameraComponent(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
	glm::mat4 camGetViewMatrix();
	glm::mat4 camGetProjMatrix(GLfloat _l = 0.0f, GLfloat _r = SCREEN_WIDTH, GLfloat _b = 0.0f, GLfloat _t = SCREEN_HEIGHT, GLfloat _n = 0.1f, GLfloat _f = 1000.0f);
	void camProcessKeyboard(CameraMovement direction, float deltaTime);
	void camProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	mat4 camTestortho(float r, float l, float t, float b, float f, float n);
	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void camProcessMouseScroll(float yoffset);
	~CameraComponent();
	void comInit();
	void comUpdate();
	void comHandleEvents();
	void comDraw();

private:
	void camUpdateCameraVectors();

};

#endif