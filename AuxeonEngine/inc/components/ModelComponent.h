#pragma once

#ifndef MODELCOMPONENT_H
#define MODELCOMPONENT_H
// helpers
#include "../inc/helpers/shader.h"
#include "../inc/helpers/stb_image.h"
#define GLM_SWIZZLE_XYZW
#define GLM_SWIZZLE_RGBA
#include "../libs/GLM-0.9.9.6/glm/glm.hpp"
#include "../libs/GLM-0.9.9.6/glm/gtx/transform.hpp"
// entities
#include "../inc/entities/Component.h"
#include "../inc/entities/GameObject.h"
// managers
#include "../inc/managers/GraphicsManager.h"
#include "../inc/managers/InputManager.h"
// components
#include "../inc/components/TransformComponent.h"

using vec2 = glm::vec2;
using vec3 = glm::vec3;
using vec4 = glm::vec4;
using mat4 = glm::mat4;
using String = std::string;

class ModelComponent : public Component
{
public:
	// singletons
	Shader* modShader;
	GraphicsManager* modGraphicsManager;

	// mat4's
	mat4 modTransform;

	float vertices[32];
	String modTexPath;
	GLuint modTexID;
	GLuint VAO, VBO, EBO;
	int modWidth;
	int modHeight;
	int modChannels;
	unsigned char* data;
	int mode;
	float32 modSize;

public:
	ModelComponent(String modTexPath = "res/textures/wall.jpg", float32 _modSize=32.0f);
	~ModelComponent();
	void comInit();
	void comHandleEvents();
	void comDraw();
	void comUpdate();

};

#endif
