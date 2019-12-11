#pragma once

#ifndef CONTROLLERCOMPONENT_H
#define CONTROLLERCOMPONENT_H


class ControllerComponent;

// state transition functions
void II(ControllerComponent* ctrl);
void IJ(ControllerComponent* ctrl);
void IL(ControllerComponent* ctrl);
void IR(ControllerComponent* ctrl);
void IK(ControllerComponent* ctrl);
void IP(ControllerComponent* ctrl);
void LI(ControllerComponent* ctrl);
void LJ(ControllerComponent* ctrl);
void LL(ControllerComponent* ctrl);
void LR(ControllerComponent* ctrl);
void LK(ControllerComponent* ctrl);
void LP(ControllerComponent* ctrl);
void RI(ControllerComponent* ctrl);
void RJ(ControllerComponent* ctrl);
void RL(ControllerComponent* ctrl);
void RR(ControllerComponent* ctrl);
void RK(ControllerComponent* ctrl);
void RP(ControllerComponent* ctrl);
void JI(ControllerComponent* ctrl);
void JJ(ControllerComponent* ctrl);
void JL(ControllerComponent* ctrl);
void JR(ControllerComponent* ctrl);
void JK(ControllerComponent* ctrl);
void JP(ControllerComponent* ctrl);
void KI(ControllerComponent* ctrl);
void KJ(ControllerComponent* ctrl);
void KL(ControllerComponent* ctrl);
void KR(ControllerComponent* ctrl);
void KK(ControllerComponent* ctrl);
void KP(ControllerComponent* ctrl);
void PI(ControllerComponent* ctrl);
void PJ(ControllerComponent* ctrl);
void PL(ControllerComponent* ctrl);
void PR(ControllerComponent* ctrl);
void PK(ControllerComponent* ctrl);
void PP(ControllerComponent* ctrl);



// helpers
#include "../libs/GLM-0.9.9.6/glm/gtx/transform.hpp"
// entities
#include "../inc/entities/Component.h"
#include "../inc/entities/GameObject.h"
// inputmanager
#include "../inc/managers/InputManager.h"
#include "../inc/managers/FrameRateManager.h"
#include "../inc/managers/GraphicsManager.h"
// components
#include "../inc/components/TransformComponent.h"
#include "../inc/components/ModelComponent.h"
#include "../inc/components/PhysicsComponent.h"
#include "../inc/components/StateMachineComponent.h"


class ControllerComponent : public Component {

public:

	//components
	PhysicsComponent* ctrlPhysicsInstance;
	StateMachineComponent* ctrlStateMachineInstance;

	//managers
	InputManager* ctrlInputManager;
	FrameRateManager* ctrlFrameRateManager;
	GraphicsManager* ctrlGraphicsManager;
	InputMap ctrlProfile;

	ControllerComponent(int inputProfile = 1);
	~ControllerComponent();

	void comInit();
	void comHandleEvents();
	void comDraw();
	void comUpdate();

public:
	// function pointers ?? how to ?? 
	void (*ctrlFSM[StateMachineComponent::TOTALNUM][StateMachineComponent::TOTALNUM])(ControllerComponent* ctrl);

};

#endif