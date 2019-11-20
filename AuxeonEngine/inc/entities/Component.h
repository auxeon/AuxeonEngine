#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

#include <array>

class GameObject;

class Component
{

public:
	GameObject* comOwner;

public:
	Component();
	virtual ~Component() = 0;
	virtual void comInit() = 0;
	virtual void comHandleEvents() = 0;
	virtual void comUpdate() = 0;
	virtual void comDraw() = 0;

};

#endif