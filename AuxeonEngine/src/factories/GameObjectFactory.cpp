#include "../inc/factories/GameObjectFactory.h"
#include "iostream"

GameObjectFactory* GameObjectFactory::gofInstance = NULL;
bool GameObjectFactory::gofInstantiated = false;


GameObjectFactory::GameObjectFactory() {

}

GameObjectFactory::~GameObjectFactory() {
	gofEraseAllObjects();
	std::cout << "GameObjectFactory : default destructed\n";
}

GameObjectFactory* GameObjectFactory::gofCreate() {
	if (NULL == gofInstance) {
		gofInstance = new GameObjectFactory();
	}
	return(gofInstance);
}

void GameObjectFactory::gofDestroy() {
	delete gofInstance;
	gofInstance = NULL;
	gofInstantiated = false;
}

bool GameObjectFactory::gofGetExists() {
	return(gofGetInstantiated());
}

bool GameObjectFactory::gofGetInstantiated() {
	return(gofInstantiated);
}


void GameObjectFactory::gofUpdate() {
	if (!gofGameObjects.empty()) {
		for (auto& go : gofGameObjects) {
			if (NULL != go.second) {
				if (go.second->gaxIsActive()) {
					go.second->gaxUpdate();
				}
			}
		}
	}
}

void GameObjectFactory::gofDraw() {
	if (!gofGameObjects.empty()) {
		for (auto& go : gofGameObjects) {
			if (NULL != go.second) {
				if (go.second->gaxIsActive()) {
					go.second->gaxDraw();
				}
			}
		}
	}
}

void GameObjectFactory::gofHandleEvents() {
	if (!gofGameObjects.empty()) {
		for (auto& go : gofGameObjects) {
			if (NULL != go.second) {
				if (go.second->gaxIsActive()) {
					go.second->gaxHandleEvents();
				}
			}
		}
	}
}


void GameObjectFactory::gofEraseInactiveObjects() {
	if (!gofGameObjects.empty()) {
		for (auto& go : gofGameObjects) {
			if (NULL != go.second) {
				if (!go.second->gaxIsActive()) {
					delete go.second;
					gofGameObjects.erase(go.first);
				}
			}
		}
	}
	std::cout << "GameObjectFactory : erased inactive gameobjects\n";
}

void GameObjectFactory::gofEraseAllObjects() {
	if (!gofGameObjects.empty()) {
		gofGameObjects.clear();
	}
	std::cout << "GameObjectFactory : erased all gameobjects\n";
}

GameObject& GameObjectFactory::gofCreateObject() {
	GameObject* tggh = new GameObject(true);
	gofGameObjects.insert(std::make_pair<int, GameObject*>(getGameObjectID(), (GameObject*)tggh));
	return(*tggh);
	std::cout << "GameObjectFactory : object "<<tggh<<" created\n";
}