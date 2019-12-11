#include "../inc/managers/PhysicsManager.h"
#include <iostream>

PhysicsManager* PhysicsManager::physicsInstance = NULL;
bool PhysicsManager::physicsInstantiated = false;

PhysicsManager* PhysicsManager::physicsCreate() {
	if (NULL == physicsInstance) {
		physicsInstance = new PhysicsManager();
	}
	return(physicsInstance);
}

void PhysicsManager::physicsDestroy() {
	delete physicsInstance;
	physicsInstance = NULL;
}


bool PhysicsManager::physicsGetInstantiated() {
	return(physicsInstantiated);
}

PhysicsManager::PhysicsManager() {
	physicsGameObjectFactoryInstance = GameObjectFactory::gofCreate();
	physicsCollisionManagerInstance = CollisionManager::colmanCreate();
	physicsFrameRateManagerInstance = FrameRateManager::fpsCreate();
	physicsInstantiated = physicsInit();
	std::cout << "PhysicsManager : default constructed" << std::endl;
}

PhysicsManager::~PhysicsManager() {
	std::cout << "PhysicsManager : default destructed" << std::endl;
}

#define GRAVITY 0.00f
void PhysicsManager::physicsUpdate(float32 _dt) {
	float dt = physicsFrameRateManagerInstance->fpsGetDeltaTime();
	for (auto& go : physicsGameObjectFactoryInstance->gofGameObjects) {
		if (go.second->gaxComponentExists<PhysicsComponent>()) {
			go.second->gaxGetComponent<PhysicsComponent>().phyIntegrate(GRAVITY, _dt);
		}
	}
	if (NULL != physicsCollisionManagerInstance) {
		physicsCollisionManagerInstance->colmanReset();
	}
}

void PhysicsManager::physicsDraw() {

}

void PhysicsManager::physicsHandleEvents() {

}

bool PhysicsManager::physicsInit() {
	std::cout << "PhysicsManager : init" << std::endl;
	return true;
}