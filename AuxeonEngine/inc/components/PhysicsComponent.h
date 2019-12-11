#pragma once

#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

// helpers
#define GLM_SWIZZLE_XYZW
#include "../libs/GLM-0.9.9.6/glm/glm.hpp"
#include "../libs/GLM-0.9.9.6/glm/gtx/transform.hpp"
#include <iostream>
// entities
#include "../inc/entities/Component.h"
#include "../inc/entities/GameObject.h"
// components
#include "../inc/components/TransformComponent.h"
#include "../inc/components/ColliderComponent.h"
#include "../inc/components/StateMachineComponent.h"
// managers
#include "../inc/managers/CollisionManager.h"
#include "../inc/managers/FrameRateManager.h"
#include "../inc/managers/TileMapManager.h"


using StateID = int;
using float32 = glm::float32;
using vec3 = glm::vec3;

class PhysicsComponent : public Component
{

public:
	vec3 phyGravity;

	vec3 phyCurrForce;
	vec3 phyPrevForce;

	vec3 phyCurrAcc;
	vec3 phyPrevAcc;

	vec3 phyCurrVel;
	vec3 phyPrevVel;

	vec3 phyCurrPos;
	vec3 phyPrevPos;

	float32 phyMass;
	float32 phyInvMass;

public:

	PhysicsComponent();
	~PhysicsComponent();

	void comInit();
	void comDraw();
	void comHandleEvents();
	void comUpdate();
	void phyIntegrate(float32 _gravity, float32 _dt);

	void testAddVelocity(vec3 _v);

public:

	TransformComponent* phyTxfInstance;
	StateMachineComponent* phyStateMachineInstance;
	ColliderComponent<Box>* phyBoxColliderInstance;
	ColliderComponent<Sphere>* phySphereColliderInstance;

	// managers
	FrameRateManager* phyFrameRateManager;
	CollisionManager* phyCollisionManager;
	TileMapManager* phyTileMapManager;
};

#endif 