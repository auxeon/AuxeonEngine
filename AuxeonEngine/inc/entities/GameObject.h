#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
// helpers
#include<unordered_map>
#include<bitset>

// entities
#include "../inc/entities/Component.h"
// components
#include "../inc/components/CameraComponent.h"
// managers
#include "../inc/managers/GraphicsManager.h"

constexpr std::size_t MAX_COMS = 16;

using ComponentBitset = std::bitset<MAX_COMS>;
using ComponentMap = std::unordered_map<int, Component*>;
using ComponentID = std::size_t;
using GameObjectID = std::size_t;


// Static component ID helpers
inline ComponentID getComponentID() {
	static ComponentID id = 0;
	return ++id;
}

template<typename T>
ComponentID getComponentType() {
	static ComponentID idType = getComponentID();
	return idType;
}

class GameObject
{

public:
	bool gaxDebugDraw;
	GameObjectID gaxID;

public:

	// obejct status
	bool gaxIsActive();

	// event update draw
	void gaxHandleEvents();
	void gaxUpdate();
	void gaxDraw();
	
	// construct destruct
	GameObject(GameObjectID id, bool active = true);
	~GameObject();
	void gaxDestroy();

	// GameObject adds components of type comType
	template<typename T, typename... TArgs>
	T& gaxAddComponent(TArgs&&... mArgs) {
		T* com(new T(std::forward<TArgs>(mArgs)...));
		com->comOwner = this;
		gaxComponentMap.insert(std::make_pair<int, Component*>(getComponentType<T>(), (T*)com));
		gaxComponentBitset[getComponentType<T>()] = 1;
		com->comInit();
		return *com;
	}

	// GameObject removes components of type comType
	template <typename T>
	bool gaxRemoveComponent() {
		if (gaxComponentMap.erase(getComponentType<T>())) {
			return true;
		}
		return false;
	}
	
	// GameObject checks if a component exists or not
	template <typename T>
	bool gaxComponentExists() const {
		return gaxComponentBitset[getComponentType<T>()];
	}


	// return the instance of the component requested assuming it exists;
	template <typename T>
	T& gaxGetComponent(){
		return *static_cast<T*>(gaxComponentMap[getComponentType<T>()]);
	}

private:

	// object defining properties
	bool gaxActive;
	GameObject* gaxParent;
	std::unordered_map<size_t, Component*> gaxComponentMap;
	ComponentBitset gaxComponentBitset;

};

#endif