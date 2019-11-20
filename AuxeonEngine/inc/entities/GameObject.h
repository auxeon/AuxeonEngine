#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
// helpers
#include<unordered_map>
#include<bitset>
#include "../inc/helpers/Vector2D.h"

// Components
#include "../inc/entities/Component.h"
#include "../inc/components/TransformComponent.h"

constexpr std::size_t MAX_COMS = 16;

using ComponentBitset = std::bitset<MAX_COMS>;
using ComponentMap = std::unordered_map<int, Component*>;
using ComponentID = std::size_t;


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
public:

	// obejct status
	bool gaxIsActive();

	// event update draw
	void gaxHandleEvents();
	void gaxUpdate();
	void gaxDraw();
	
	// construct destruct
	GameObject(bool active = true);
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