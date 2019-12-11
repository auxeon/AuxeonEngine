#pragma once

#ifndef STATEMACHINECOMPONENT_H
#define STATEMACHINECOMPONENT_H

// helpers
#define GLM_SWIZZLE_XYZW
#include "../libs/GLM-0.9.9.6/glm/glm.hpp"
#include <iostream>
//entities
#include "../inc/entities/Component.h"
#include "../inc/entities/GameObject.h"
// components;

using StateID = int;
using float32 = glm::float32;


class StateMachineComponent : public Component
{
public:

	enum smcLegalStates {
		IDLE = 0,
		RUN_LEFT,
		RUN_RIGHT,
		JUMP,
		PUNCH,
		KICK,
		TOTALNUM
	};

	// state def
	StateID smcCurrState;
	StateID smcPrevState;

	// where is the object wrt the tilemap blocks
	bool smcPrevTouchRight;
	bool smcCurrTouchRight;

	bool smcPrevTouchLeft;
	bool smcCurrTouchLeft;

	bool smcPrevTouchUp;
	bool smcCurrTouchUp;

	bool smcPrevTouchDown;
	bool smcCurrTouchDown;

	// state variables
	float32 smcActionSpeed;

public:

	StateMachineComponent(float32 _smcSpeed = 1.0f);
	~StateMachineComponent();

	void comInit();
	void comDraw();
	void comHandleEvents();
	void comUpdate();

};

#endif