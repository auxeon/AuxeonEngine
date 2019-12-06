#include "../inc/entities/GameObject.h"

// returns current objct active status
bool GameObject::gaxIsActive() {
	return gaxActive;
}

void GameObject::gaxDestroy() {
	gaxActive = false;
}

// Assumption is that you can't create any object with out a position.
GameObject::GameObject(GameObjectID id, bool active) : gaxDebugDraw(false), gaxActive(active), gaxParent(NULL), gaxID(id){
	std::cout << "GameObject : " << this << " created\n";
}
// GameObject destroyer
GameObject::~GameObject() {


	for (auto& com : gaxComponentMap) {
		delete com.second;
	}

	if (!gaxComponentMap.empty()) {
		gaxComponentMap.clear();
	}

	std::cout << "GameObject : " << this << " destroyed\n";
}

// GameObject HandleEvent calls
void GameObject::gaxHandleEvents() {
	if (!gaxComponentMap.empty()) {
		for (auto& component : gaxComponentMap) {
			component.second->comHandleEvents();
		}
	}
}

// GameObject Update calls
void GameObject::gaxUpdate() {
	if (!gaxComponentMap.empty()) {
		for (auto& component : gaxComponentMap) {
			component.second->comUpdate();
		}
	}
}

// GameObject Draw calls
void GameObject::gaxDraw() {
	if (!gaxComponentMap.empty()) {
		for (auto& component : gaxComponentMap) {
			component.second->comDraw();
		}
	}
}
