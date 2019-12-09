#pragma once

#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

// entities
#include "../inc/entities/Component.h"
#include "../inc/entities/GameObject.h"
// helpers
#include<unordered_map>



using ContactID = std::size_t;
using ContactMap = std::unordered_map<int , std::pair<GameObject*, GameObject*>>;

// Helpers for Game Object ID
// need to inline this guys as global functions - if any files include them, across all files that include this breaks
// you get function already defined in some other transaltion unit (.OBJ) errors
inline ContactID getGameObjectID() {
	static ContactID contactID = 0;
	return ++contactID;
}

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

};

#endif