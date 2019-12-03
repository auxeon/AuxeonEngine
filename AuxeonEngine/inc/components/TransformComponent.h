#pragma once

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H
// helpers
#define GLM_SWIZZLE_XYZW
#define GLM_SWIZZLE_RGBA
#include "../libs/GLM-0.9.9.6/glm/glm.hpp"
#include "../libs/GLM-0.9.9.6/glm/gtx/transform.hpp"

// entities
#include "../inc/entities/Component.h"
#include "../inc/entities/GameObject.h"

using mat4 = glm::mat4;
using vec3 = glm::vec3;

class TransformComponent : public Component{

public:
	// objects orientation in 3D space
	vec3 txfWorldUpVec;
	vec3 txfPosition;
	vec3 txfTarget;
	vec3 txfLookVec;
	vec3 txfUpVec;
	vec3 txfRightVec;

	mat4 txfRotMat;
	mat4 txfTraMat;
	mat4 txfScaMat;

	float txfMaxSpeed;
	
public:
	TransformComponent();
	TransformComponent(float x , float y, float max_speed=1.0f);
	~TransformComponent();

	void txfRotate(float _theta);
	void txfTranslate(float _x, float _y);

	void comInit();
	void comHandleEvents();
	void comDraw();
	void comUpdate();


};

#endif