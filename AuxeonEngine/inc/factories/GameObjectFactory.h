#pragma once

#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

// entities
#include "../inc/entities/GameObject.h"
// components
#include "../inc/components/TransformComponent.h"
#include "../inc/components/CameraComponent.h"
// managers
#include "../inc/managers/GraphicsManager.h"

using GameObjectID = std::size_t;
using GameObjectMap = std::unordered_map<int, GameObject*>;

// Helpers for Game Object ID
inline GameObjectID getGameObjectID() {
	static GameObjectID objectID = 0;
	return ++objectID;
}

class GameObjectFactory
{

public:
	static GameObjectFactory* gofCreate();
	static void gofInit();
	static bool gofGetInstantiated();
	static void gofDestroy();
	bool gofGetExists();

	void gofUpdate();
	void gofDraw();
	void gofHandleEvents();

	void gofEraseInactiveObjects();
	void gofEraseAllObjects();
	GameObject& gofCreateObject();

private:
	// self
	GameObjectFactory();
	~GameObjectFactory();
	static GameObjectFactory* gofInstance;
	static bool gofInstantiated;

	GameObjectMap gofGameObjects;

};

#endif