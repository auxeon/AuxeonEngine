#pragma once

#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

// entities
#include "../inc/entities/GameObject.h"
#include "../inc/entities/Component.h"
// factories
#include "../inc/factories/GameObjectFactory.h"
// managers
#include "../inc/managers/CollisionManager.h"
// components
#include "../inc/components/PhysicsComponent.h"


class PhysicsManager
{
public:
	static PhysicsManager* physicsCreate();
	static void physicsDestroy();
	static bool physicsGetInstantiated();

	void physicsUpdate(float32 _dt);
	void physicsDraw();
	void physicsHandleEvents();

private:
	static PhysicsManager* physicsInstance;
	static bool physicsInstantiated;
	GameObjectFactory* physicsGameObjectFactoryInstance;
	CollisionManager* physicsCollisionManagerInstance;
	FrameRateManager* physicsFrameRateManagerInstance;

private:
	PhysicsManager();
	~PhysicsManager();
	bool physicsInit();

};

#endif