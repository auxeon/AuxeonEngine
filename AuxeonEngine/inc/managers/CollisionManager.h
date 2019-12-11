#pragma once

#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

// entities
#include "../inc/entities/Component.h"
#include "../inc/entities/GameObject.h"
// components
#include "../inc/components/ColliderComponent.h"
// managers
#include "../inc/managers/GraphicsManager.h"
// factories
#include "../inc/factories/GameObjectFactory.h"
// helpers
#include<unordered_map>

using ContactID = std::size_t;
using ContactPair = std::pair<GameObject*, GameObject*>;
using ContactMap = std::unordered_map<int, ContactPair>;
using ContactMapPair = std::pair<ContactID, ContactPair>;

// Helpers for Contact ID
// need to inline this guys as global functions - if any files include them, across all files that include this breaks
// you get function already defined in some other transaltion unit (.OBJ) errors
inline ContactID getContactID() {
	static ContactID contactID = 0;
	return ++contactID;
}

class CollisionManager
{

public:
	static CollisionManager* colmanCreate();
	static bool colmanInit();
	static bool colmanGetInstantiated();
	static void colmanDestroy();
	bool colmanGetExists();

	void colmanUpdate();
	void colmanDraw();
	void colmanHandleEvents();

	void colmanReset();
	void colmanEraseAllContacts();
	bool colmanEraseContact(ContactID _cid);
	ContactID colmanCreateContact(GameObject* _a, GameObject* _b);
	bool colmanContactCheckCollide(GameObject* _go1, GameObject* _go2);

private:
	CollisionManager();
	~CollisionManager();
	static bool colmanInstantiated;
	static CollisionManager* colmanInstance;
	GameObjectFactory* colmanGameObjectFactoryInstance;
	GraphicsManager* colmanGraphicsManager;
	ContactMap colmanContactMap;
};

#endif