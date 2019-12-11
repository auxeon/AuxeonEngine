#include "../inc/components/ControllerComponent.h"

ControllerComponent::ControllerComponent(int inputProfile) {

	ctrlInputManager = InputManager::inmCreate();
	ctrlFrameRateManager = FrameRateManager::fpsCreate();
	ctrlGraphicsManager = GraphicsManager::gfxCreate();

	ctrlProfile = ctrlInputManager->inmGetProfile(inputProfile);

	//setting functionpointers
	ctrlFSM[StateMachineComponent::IDLE][StateMachineComponent::IDLE] = II;
	ctrlFSM[StateMachineComponent::IDLE][StateMachineComponent::JUMP] = IJ;
	ctrlFSM[StateMachineComponent::IDLE][StateMachineComponent::RUN_LEFT] = IR;
	ctrlFSM[StateMachineComponent::IDLE][StateMachineComponent::RUN_RIGHT] = IL;
	ctrlFSM[StateMachineComponent::IDLE][StateMachineComponent::KICK] = IK;
	ctrlFSM[StateMachineComponent::IDLE][StateMachineComponent::PUNCH] = IP;

	ctrlFSM[StateMachineComponent::JUMP][StateMachineComponent::IDLE] = JI;
	ctrlFSM[StateMachineComponent::JUMP][StateMachineComponent::JUMP] = JJ;
	ctrlFSM[StateMachineComponent::JUMP][StateMachineComponent::RUN_LEFT] = JR;
	ctrlFSM[StateMachineComponent::JUMP][StateMachineComponent::RUN_RIGHT] = JL;
	ctrlFSM[StateMachineComponent::JUMP][StateMachineComponent::KICK] = JK;
	ctrlFSM[StateMachineComponent::JUMP][StateMachineComponent::PUNCH] = JP;

	ctrlFSM[StateMachineComponent::RUN_LEFT][StateMachineComponent::IDLE] = LI;
	ctrlFSM[StateMachineComponent::RUN_LEFT][StateMachineComponent::JUMP] = LJ;
	ctrlFSM[StateMachineComponent::RUN_LEFT][StateMachineComponent::RUN_LEFT] = LL;
	ctrlFSM[StateMachineComponent::RUN_LEFT][StateMachineComponent::RUN_RIGHT] = LR;
	ctrlFSM[StateMachineComponent::RUN_LEFT][StateMachineComponent::KICK] = LK;
	ctrlFSM[StateMachineComponent::RUN_LEFT][StateMachineComponent::PUNCH] = LP;

	ctrlFSM[StateMachineComponent::RUN_RIGHT][StateMachineComponent::IDLE] = RI;
	ctrlFSM[StateMachineComponent::RUN_RIGHT][StateMachineComponent::JUMP] = RJ;
	ctrlFSM[StateMachineComponent::RUN_RIGHT][StateMachineComponent::RUN_LEFT] = RL;
	ctrlFSM[StateMachineComponent::RUN_RIGHT][StateMachineComponent::RUN_RIGHT] = RR;
	ctrlFSM[StateMachineComponent::RUN_RIGHT][StateMachineComponent::KICK] = RK;
	ctrlFSM[StateMachineComponent::RUN_RIGHT][StateMachineComponent::PUNCH] = RP;

	ctrlFSM[StateMachineComponent::KICK][StateMachineComponent::IDLE] = KI;
	ctrlFSM[StateMachineComponent::KICK][StateMachineComponent::JUMP] = KJ;
	ctrlFSM[StateMachineComponent::KICK][StateMachineComponent::RUN_LEFT] = KL;
	ctrlFSM[StateMachineComponent::KICK][StateMachineComponent::RUN_RIGHT] = KR;
	ctrlFSM[StateMachineComponent::KICK][StateMachineComponent::KICK] = KK;
	ctrlFSM[StateMachineComponent::KICK][StateMachineComponent::PUNCH] = KP;

	ctrlFSM[StateMachineComponent::PUNCH][StateMachineComponent::IDLE] = PI;
	ctrlFSM[StateMachineComponent::PUNCH][StateMachineComponent::JUMP] = PJ;
	ctrlFSM[StateMachineComponent::PUNCH][StateMachineComponent::RUN_LEFT] = PL;
	ctrlFSM[StateMachineComponent::PUNCH][StateMachineComponent::RUN_RIGHT] = PR;
	ctrlFSM[StateMachineComponent::PUNCH][StateMachineComponent::KICK] = PK;
	ctrlFSM[StateMachineComponent::PUNCH][StateMachineComponent::PUNCH] = PP;


}

ControllerComponent::~ControllerComponent() {

}

void ControllerComponent::comInit() {

}

void ControllerComponent::comUpdate() {
	
	if (!comOwner->gaxComponentExists<TransformComponent>()) {
		return;
	}

	float speed = 200.0f;
	float dt = ctrlFrameRateManager->fpsGetDeltaTime();

	// movement controls 

	if (ctrlInputManager->inmIsKeyTriggered(ctrlProfile["JUMP"])) {
		//comOwner->gaxGetComponent<TransformComponent>().txfPosition.y += dt*speed;
		//comOwner->gaxGetComponent<TransformComponent>().txfTraMat = glm::translate(comOwner->gaxGetComponent<TransformComponent>().txfTraMat, glm::vec3(0, dt*speed, 0));
		comOwner->gaxGetComponent<PhysicsComponent>().phyCurrForce.y = 100.0f;
	}
	if (ctrlInputManager->inmIsKeyPressed(ctrlProfile["UP"])) {
		//comOwner->gaxGetComponent<TransformComponent>().txfPosition.y += dt*speed;
		//comOwner->gaxGetComponent<TransformComponent>().txfTraMat = glm::translate(comOwner->gaxGetComponent<TransformComponent>().txfTraMat, glm::vec3(0, dt*speed, 0));
		comOwner->gaxGetComponent<PhysicsComponent>().phyCurrVel.y = 100.0f;
	}
	else if (ctrlInputManager->inmIsKeyPressed(ctrlProfile["DOWN"])) {
		//comOwner->gaxGetComponent<TransformComponent>().txfPosition.y -= dt*speed;
		//comOwner->gaxGetComponent<TransformComponent>().txfTraMat = glm::translate(comOwner->gaxGetComponent<TransformComponent>().txfTraMat, glm::vec3(0, -dt*speed, 0));
		comOwner->gaxGetComponent<PhysicsComponent>().phyCurrVel.y = -100.0f;
	}

	if (ctrlInputManager->inmIsKeyPressed(ctrlProfile["RUN_LEFT"])) {
		//comOwner->gaxGetComponent<TransformComponent>().txfPosition.x -= dt*speed;
		//comOwner->gaxGetComponent<TransformComponent>().txfTraMat = glm::translate(comOwner->gaxGetComponent<TransformComponent>().txfTraMat, glm::vec3(-dt*speed, 0, 0));
		comOwner->gaxGetComponent<PhysicsComponent>().phyCurrVel.x = -100.0f;
	}

	else if (ctrlInputManager->inmIsKeyPressed(ctrlProfile["RUN_RIGHT"])) {
		//comOwner->gaxGetComponent<TransformComponent>().txfPosition.x += dt*speed;
		//comOwner->gaxGetComponent<TransformComponent>().txfTraMat = glm::translate(comOwner->gaxGetComponent<TransformComponent>().txfTraMat, glm::vec3(dt*speed, 0, 0));
		comOwner->gaxGetComponent<PhysicsComponent>().phyCurrVel.x = 100.0f;
	}
	//else{ comOwner->gaxGetComponent<PhysicsComponent>().phyCurrVel.x = 0.0f; }

	//if (ctrlInputManager->inmIsKeyPressed(ctrlProfile["ROT_RIGHT"])) {
	//	comOwner->gaxGetComponent<TransformComponent>().txfRotMat = glm::rotate(comOwner->gaxGetComponent<TransformComponent>().txfRotMat, glm::radians(-0.1f), glm::vec3(0, 0, 1));
	//}
	//if (ctrlInputManager->inmIsKeyPressed(ctrlProfile["ROT_LEFT"])) {
	//	comOwner->gaxGetComponent<TransformComponent>().txfRotMat = glm::rotate(comOwner->gaxGetComponent<TransformComponent>().txfRotMat, glm::radians(0.1f), glm::vec3(0, 0, 1));
	//}
	if (ctrlInputManager->inmIsKeyTriggered(ctrlProfile["TEXTURE_TOGGLE"]) ){
		std::cout << "debug draw pressed" << std::endl;
		ctrlGraphicsManager->gfxDebugDraw = !ctrlGraphicsManager->gfxDebugDraw;
		std::cout << "debug draw : " << ctrlGraphicsManager->gfxDebugDraw << std::endl;
	}

}

void ControllerComponent::comDraw() {

}

void ControllerComponent::comHandleEvents() {

}


// FSM transition functions		

// helper functions for state transitions 

// DONT CALL REAL I/L/R/J/K/P functions here - it's gonna be cyclic otherwise
void II(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			std::cout << "IDLE\n";
			// current state specific
			ctrl->ctrlPhysicsInstance->phyCurrVel = vec3(0.0f, 0.0f, 0.0f);

			// other state transitions
			// if jumping in the air
			if (!ctrl->ctrlStateMachineInstance->smcCurrTouchDown) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::JUMP;
			}
			// if both right and left pressed or not pressed
			if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_RIGHT"]) == ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_LEFT"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::IDLE;
				ctrl->ctrlPhysicsInstance->phyCurrVel = vec3(0.0f, 0.0f, 0.0f);
			}
			// if right and not left
			else if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_RIGHT"]) && !ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_LEFT"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::RUN_RIGHT;
				if (ctrl->ctrlStateMachineInstance->smcCurrTouchRight) {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = 0.0f;
				}
				else {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = ctrl->ctrlStateMachineInstance->smcActionSpeed;
				}
			}
			// if not right and left
			else if (!ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_RIGHT"]) && ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_LEFT"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::RUN_LEFT;
				if (ctrl->ctrlStateMachineInstance->smcCurrTouchLeft) {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = 0.0f;
				}
				else {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = -ctrl->ctrlStateMachineInstance->smcActionSpeed;
				}
			}
			else if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["JUMP"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::JUMP;
				if (ctrl->ctrlStateMachineInstance->smcCurrTouchUp) {
					ctrl->ctrlPhysicsInstance->phyCurrVel.y = 0.0f;
				}
				else {
					ctrl->ctrlPhysicsInstance->phyCurrVel.y = ctrl->ctrlStateMachineInstance->smcActionSpeed;
				}
			}
			else if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["KICK"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::KICK;
			}
			else if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["PUNCH"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::PUNCH;
			}
		}
	}
	return;
}
void IJ(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "IDLE -> JUMP\n";
			// play JUMP sound
			// done with all the IJ transitions
			// now actually JUMP
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->JUMP][ctrl->ctrlStateMachineInstance->JUMP](ctrl);
			// other state transitions
		}
	}
	return;
}
void IL(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "IDLE -> RUN_LEFT\n";
			//play RUN_LEFT sound
			// done with all the IL transitions
			// now actually RUN_LEFT
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->RUN_LEFT][ctrl->ctrlStateMachineInstance->RUN_LEFT](ctrl);
			// other state transitions
		}
	}
	return;
}
void IR(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "IDLE -> RUN_RIGHT\n";
			//play RUN_RIGHT sound
			// done with all the IR transitions
			// now actually RUN_RIGHT
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->RUN_RIGHT][ctrl->ctrlStateMachineInstance->RUN_RIGHT](ctrl);
			// other state transitions
		}
	}
	return;
}
void IK(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "IDLE -> KICK\n";
			//play KICK sound
			// done with all the IK transitions
			// now actually KICK
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->KICK][ctrl->ctrlStateMachineInstance->KICK](ctrl);
			// other state transitions
		}
	}
	return;
}
void IP(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "IDLE -> PUNCH\n";
			//play PUNCH sound
			// done with all the IP transitions
			// now actually PUNCH
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->PUNCH][ctrl->ctrlStateMachineInstance->PUNCH](ctrl);
			// other state transitions
		}
	}
	return;
}
void LI(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "RUN_LEFT -> IDLE\n";
			//play RUN_LEFT IDLE sound
			// done with all the LI transitions
			// now actually IDLE
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->IDLE][ctrl->ctrlStateMachineInstance->IDLE](ctrl);
			// other state transitions
		}
	}
	return;
}
void LJ(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "RUN_LEFT -> JUMP\n";
			//play RUN_LEFT JUMP sound
			// done with all the LJ transitions
			// now actually RUN_RIGHT
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->JUMP][ctrl->ctrlStateMachineInstance->JUMP](ctrl);
			// other state transitions
		}
	}
	return;
}

// DONT CALL REAL I/L/R/J/K/P functions here - it's gonna be cyclic otherwise
void LL(ControllerComponent* ctrl) {

	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			std::cout << "LEFT\n";
			// current state specific

			// if both right and left pressed or not pressed
			if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_RIGHT"]) == ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_LEFT"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::IDLE;
				ctrl->ctrlPhysicsInstance->phyCurrVel = vec3(0.0f, 0.0f, 0.0f);
			}
			// if right and not left
			else if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_RIGHT"]) && !ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_LEFT"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::RUN_RIGHT;
				if (ctrl->ctrlStateMachineInstance->smcCurrTouchRight) {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = 0.0f;
				}
				else {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = ctrl->ctrlStateMachineInstance->smcActionSpeed;
				}
			}
			// if not right and left
			else if (!ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_RIGHT"]) && ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_LEFT"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::RUN_LEFT;
				if (ctrl->ctrlStateMachineInstance->smcCurrTouchLeft) {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = 0.0f;
				}
				else {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = -ctrl->ctrlStateMachineInstance->smcActionSpeed;
				}
			}
			// Do later
			else if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["KICK"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::KICK;
			}
			else if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["PUNCH"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::PUNCH;
			}

			// jump key is currently pressed;
			if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["JUMP"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::JUMP;
				if (ctrl->ctrlStateMachineInstance->smcCurrTouchUp) {
					ctrl->ctrlPhysicsInstance->phyCurrVel.y = 0.0f;
				}
				else {
					ctrl->ctrlPhysicsInstance->phyCurrVel.y = ctrl->ctrlStateMachineInstance->smcActionSpeed;
				}
			}
			// if not on ground 
			else if (!ctrl->ctrlStateMachineInstance->smcCurrTouchDown) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::JUMP;
			}

		}
	}
	return;
}
void LR(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "RUN_LEFT -> RUN_RIGHT\n";
			//play RUN_LEFT RUN_RIGHT sound
			// done with all the LR transitions
			// now actually RUN_RIGHT
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->RUN_RIGHT][ctrl->ctrlStateMachineInstance->RUN_RIGHT](ctrl);
			// other state transitions
		}
	}
	return;
}
void LK(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "RUN_LEFT -> KICK\n";
			//play RUN_LEFT KICK sound
			// done with all the LK transitions
			// now actually KICK
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->KICK][ctrl->ctrlStateMachineInstance->KICK](ctrl);
			// other state transitions
		}
	}
	return;
}
void LP(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "RUN_LEFT -> PUNCH\n";
			//play RUN_LEFT PUNCH sound
			// done with all the LP transitions
			// now actually RUN_RIGHT
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->PUNCH][ctrl->ctrlStateMachineInstance->PUNCH](ctrl);
			// other state transitions
		}
	}
	return;
}
void RI(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "RUN_RIGHT -> IDLE\n";
			//play RUN_LEFT IDLE sound
			// done with all the RI transitions
			// now actually IDLE
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->IDLE][ctrl->ctrlStateMachineInstance->IDLE](ctrl);
			// other state transitions
		}
	}
	return;
}
void RJ(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "RUN_RIGHT -> JUMP\n";
			//play RUN_LEFT JUMP sound
			// done with all the RJ transitions
			// now actually JUMP
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->JUMP][ctrl->ctrlStateMachineInstance->JUMP](ctrl);
			// other state transitions
		}
	}
	return;
}
void RL(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "RUN_RIGHT -> RUN_LEFT\n";
			//play RUN_RIGHT RUN_LEFT sound
			// done with all the RL transitions
			// now actually RUN_LEFT
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->RUN_RIGHT][ctrl->ctrlStateMachineInstance->RUN_RIGHT](ctrl);
			// other state transitions
		}
	}
	return;
}

// DONT CALL REAL I/L/R/J/K/P functions here - it's gonna be cyclic otherwise
void RR(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			std::cout << "RIGHT\n";
			// current state specific

			// if both right and left pressed or not pressed
			if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_RIGHT"]) == ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_LEFT"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::IDLE;
				ctrl->ctrlPhysicsInstance->phyCurrVel = vec3(0.0f, 0.0f, 0.0f);
			}
			// if right and not left
			else if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_RIGHT"]) && !ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_LEFT"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::RUN_RIGHT;
				if (ctrl->ctrlStateMachineInstance->smcCurrTouchRight) {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = 0.0f;
				}
				else {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = ctrl->ctrlStateMachineInstance->smcActionSpeed;
				}
			}
			// if not right and left
			else if (!ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_RIGHT"]) && ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_LEFT"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::RUN_LEFT;
				if (ctrl->ctrlStateMachineInstance->smcCurrTouchLeft) {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = 0.0f;
				}
				else {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = -ctrl->ctrlStateMachineInstance->smcActionSpeed;
				}
			}
			// Do later
			else if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["KICK"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::KICK;
			}
			else if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["PUNCH"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::PUNCH;
			}

			// jump key is currently pressed;
			if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["JUMP"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::JUMP;
				if (ctrl->ctrlStateMachineInstance->smcCurrTouchUp) {
					ctrl->ctrlPhysicsInstance->phyCurrVel.y = 0.0f;
				}
				else {
					ctrl->ctrlPhysicsInstance->phyCurrVel.y = ctrl->ctrlStateMachineInstance->smcActionSpeed;
				}
			}
			// if not on ground 
			else if (!ctrl->ctrlStateMachineInstance->smcCurrTouchDown) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::JUMP;
			}

		}
	}
	return;
}

void RK(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "RUN_RIGHT -> KICK\n";
			//play RUN_RIGHT KICK sound
			// done with all the RK transitions
			// now actually KICK
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->KICK][ctrl->ctrlStateMachineInstance->KICK](ctrl);
			// other state transitions
		}
	}
	return;
}
void RP(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "RUN_RIGHT -> PUNCH\n";
			//play RUN_RIGHT PUNCH sound
			// done with all the RP transitions
			// now actually PUNCH
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->PUNCH][ctrl->ctrlStateMachineInstance->PUNCH](ctrl);
			// other state transitions
		}
	}
	return;
}
void JI(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "JUMP -> IDLE\n";
			//play JUMP IDLE sound
			// done with all the JI transitions
			// now actually IDLE
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->IDLE][ctrl->ctrlStateMachineInstance->IDLE](ctrl);
			// other state transitions
		}
	}
	return;
}

// DONT CALL REAL I/L/R/J/K/P functions here - it's gonna be cyclic otherwise
void JJ(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			std::cout << "JUMP\n";
			// current state specific
			ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::JUMP;
			if (ctrl->ctrlStateMachineInstance->smcCurrTouchUp) {
				ctrl->ctrlPhysicsInstance->phyCurrVel.y = 0.0f;
			}
			else {
				ctrl->ctrlPhysicsInstance->phyCurrVel.y = ctrl->ctrlStateMachineInstance->smcActionSpeed;
			}

			// if both right and left pressed or not pressed
			if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_RIGHT"]) == ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_LEFT"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::IDLE;
				ctrl->ctrlPhysicsInstance->phyCurrVel.x = 0.0f;
			}
			// if right and not left
			else if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_RIGHT"]) && !ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_LEFT"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::RUN_RIGHT;
				if (ctrl->ctrlStateMachineInstance->smcCurrTouchRight) {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = 0.0f;
				}
				else {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = ctrl->ctrlStateMachineInstance->smcActionSpeed;
				}
			}
			// if not right and left
			else if (!ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_RIGHT"]) && ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_LEFT"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::RUN_LEFT;
				if (ctrl->ctrlStateMachineInstance->smcCurrTouchLeft) {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = 0.0f;
				}
				else {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = -ctrl->ctrlStateMachineInstance->smcActionSpeed;
				}
			}
			// Do later
			else if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["KICK"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::KICK;
			}
			else if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["PUNCH"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::PUNCH;
			}

			// jump key is currently pressed;
			if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["JUMP"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::JUMP;
				if (ctrl->ctrlStateMachineInstance->smcCurrTouchUp) {
					ctrl->ctrlPhysicsInstance->phyCurrVel.y = 0.0f;
				}
				else {
					ctrl->ctrlPhysicsInstance->phyCurrVel.y = ctrl->ctrlStateMachineInstance->smcActionSpeed;
				}
			}
			// if we hit the ground 
			else if (ctrl->ctrlStateMachineInstance->smcCurrTouchDown) {
				// if both right and left pressed or not pressed
				if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_RIGHT"]) == ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_LEFT"])) {
					ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::IDLE;
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = 0.0f;
				}
				// if right and not left
				else if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_RIGHT"]) && !ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_LEFT"])) {
					ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::RUN_RIGHT;
					if (ctrl->ctrlStateMachineInstance->smcCurrTouchRight) {
						ctrl->ctrlPhysicsInstance->phyCurrVel.x = 0.0f;
					}
					else {
						ctrl->ctrlPhysicsInstance->phyCurrVel.x = ctrl->ctrlStateMachineInstance->smcActionSpeed;
					}
				}
				// if not right and left
				else if (!ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_RIGHT"]) && ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_LEFT"])) {
					ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::RUN_LEFT;
					if (ctrl->ctrlStateMachineInstance->smcCurrTouchLeft) {
						ctrl->ctrlPhysicsInstance->phyCurrVel.x = 0.0f;
					}
					else {
						ctrl->ctrlPhysicsInstance->phyCurrVel.x = -ctrl->ctrlStateMachineInstance->smcActionSpeed;
					}
				}
			}

		}
	}
	return;
}
void JL(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "JUMP -> RUN_LEFT\n";
			//play JUMP RUN_LEFT sound
			// done with all the JL transitions
			// now actually RUN_LEFT
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->RUN_LEFT][ctrl->ctrlStateMachineInstance->RUN_LEFT](ctrl);
			// other state transitions
		}
	}
	return;
}
void JR(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "JUMP -> RUN_RIGHT\n";
			//play JUMP RUN_RIGHT sound
			// done with all the JR transitions
			// now actually RUN_RIGHT
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->RUN_RIGHT][ctrl->ctrlStateMachineInstance->RUN_RIGHT](ctrl);
			// other state transitions
		}
	}
	return;
}
void JK(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "JUMP -> KICK\n";
			//play JUMP KICK sound
			// done with all the JK transitions
			// now actually KICK
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->KICK][ctrl->ctrlStateMachineInstance->KICK](ctrl);
			// other state transitions
		}
	}
	return;
}
void JP(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "JUMP -> PUNCH\n";
			//play JUMP PUNCH sound
			// done with all the JP transitions
			// now actually PUNCH
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->PUNCH][ctrl->ctrlStateMachineInstance->PUNCH](ctrl);
			// other state transitions
		}
	}
	return;
}
void KI(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "KICK -> IDLE\n";
			//play KICK IDLE sound
			// done with all the KI transitions
			// now actually IDLE
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->IDLE][ctrl->ctrlStateMachineInstance->IDLE](ctrl);
			// other state transitions
		}
	}
	return;
}
void KJ(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "KICK -> JUMP\n";
			//play KICK JUMP sound
			// done with all the KJ transitions
			// now actually JUMP
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->JUMP][ctrl->ctrlStateMachineInstance->JUMP](ctrl);
			// other state transitions
		}
	}
	return;
}
void KL(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "KICK -> RUN_LEFT\n";
			//play KICK RUN_LEFT sound
			// done with all the KL transitions
			// now actually RUN_LEFT
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->RUN_LEFT][ctrl->ctrlStateMachineInstance->RUN_LEFT](ctrl);
			// other state transitions
		}
	}
	return;
}
void KR(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "KICK -> RUN_RIGHT\n";
			//play KICK RUN_RIGHT sound
			// done with all the KR transitions
			// now actually RUN_LEFT
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->RUN_RIGHT][ctrl->ctrlStateMachineInstance->RUN_RIGHT](ctrl);
			// other state transitions
		}
	}
	return;
}

// DONT CALL REAL I/L/R/J/K/P functions here - it's gonna be cyclic otherwise
void KK(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			std::cout << "KICK\n";
			// current state specific

			// if both right and left pressed or not pressed
			if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_RIGHT"]) == ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_LEFT"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::IDLE;
				ctrl->ctrlPhysicsInstance->phyCurrVel = vec3(0.0f, 0.0f, 0.0f);
			}
			// if right and not left
			else if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_RIGHT"]) && !ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_LEFT"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::RUN_RIGHT;
				if (ctrl->ctrlStateMachineInstance->smcCurrTouchRight) {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = 0.0f;
				}
				else {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = ctrl->ctrlStateMachineInstance->smcActionSpeed;
				}
			}
			// if not right and left
			else if (!ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_RIGHT"]) && ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_LEFT"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::RUN_LEFT;
				if (ctrl->ctrlStateMachineInstance->smcCurrTouchLeft) {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = 0.0f;
				}
				else {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = -ctrl->ctrlStateMachineInstance->smcActionSpeed;
				}
			}
			// Do later
			else if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["KICK"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::KICK;
			}
			else if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["PUNCH"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::PUNCH;
			}

			// jump key is currently pressed;
			if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["JUMP"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::JUMP;
				if (ctrl->ctrlStateMachineInstance->smcCurrTouchUp) {
					ctrl->ctrlPhysicsInstance->phyCurrVel.y = 0.0f;
				}
				else {
					ctrl->ctrlPhysicsInstance->phyCurrVel.y = ctrl->ctrlStateMachineInstance->smcActionSpeed;
				}
			}
			// if not on ground 
			else if (!ctrl->ctrlStateMachineInstance->smcCurrTouchDown) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::JUMP;
			}

		}
	}
	return;
}
void KP(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "KICK -> PUNCH\n";
			//play KICK PUNCH sound
			// done with all the KP transitions
			// now actually PUNCH
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->PUNCH][ctrl->ctrlStateMachineInstance->PUNCH](ctrl);
			// other state transitions
		}
	}
	return;
}
void PI(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "PUNCH -> IDLE\n";
			//play PUNCH IDLE sound
			// done with all the PI transitions
			// now actually IDLE
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->IDLE][ctrl->ctrlStateMachineInstance->IDLE](ctrl);
			// other state transitions
		}
	}
	return;
}
void PJ(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "PUNCH -> JUMP\n";
			//play PUNCH JUMP sound
			// done with all the PJ transitions
			// now actually JUMP
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->JUMP][ctrl->ctrlStateMachineInstance->JUMP](ctrl);
			// other state transitions
		}
	}
	return;
}
void PL(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "PUNCH -> RUN_LEFT\n";
			//play PUNCH RUN_LEFT sound
			// done with all the PL transitions
			// now actually RUN_LEFT
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->RUN_LEFT][ctrl->ctrlStateMachineInstance->RUN_LEFT](ctrl);
			// other state transitions
		}
	}
	return;
}
void PR(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "PUNCH -> RUN_RIGHT\n";
			//play PUNCH RUN_RIGHT sound
			// done with all the PR transitions
			// now actually RUN_LEFT
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->RUN_RIGHT][ctrl->ctrlStateMachineInstance->RUN_RIGHT](ctrl);
			// other state transitions
		}
	}
	return;
}
void PK(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			// current state specific
			std::cout << "PUNCH -> KICK\n";
			//play PUNCH KICK sound
			// done with all the PK transitions
			// now actually KICK
			ctrl->ctrlFSM[ctrl->ctrlStateMachineInstance->KICK][ctrl->ctrlStateMachineInstance->KICK](ctrl);
			// other state transitions
		}
	}
	return;
}

// DONT CALL REAL I/L/R/J/K/P functions here - it's gonna be cyclic otherwise
void PP(ControllerComponent* ctrl) {
	if (NULL != ctrl) {
		if (NULL != ctrl->ctrlStateMachineInstance) {
			std::cout << "PUNCH\n";
			// current state specific

			// if both right and left pressed or not pressed
			if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_RIGHT"]) == ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_LEFT"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::IDLE;
				ctrl->ctrlPhysicsInstance->phyCurrVel = vec3(0.0f, 0.0f, 0.0f);
			}
			// if right and not left
			else if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_RIGHT"]) && !ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_LEFT"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::RUN_RIGHT;
				if (ctrl->ctrlStateMachineInstance->smcCurrTouchRight) {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = 0.0f;
				}
				else {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = ctrl->ctrlStateMachineInstance->smcActionSpeed;
				}
			}
			// if not right and left
			else if (!ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_RIGHT"]) && ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["RUN_LEFT"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::RUN_LEFT;
				if (ctrl->ctrlStateMachineInstance->smcCurrTouchLeft) {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = 0.0f;
				}
				else {
					ctrl->ctrlPhysicsInstance->phyCurrVel.x = -ctrl->ctrlStateMachineInstance->smcActionSpeed;
				}
			}
			// Do later
			else if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["KICK"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::KICK;
			}
			else if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["PUNCH"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::PUNCH;
			}

			// jump key is currently pressed;
			if (ctrl->ctrlInputManager->inmIsKeyPressed(ctrl->ctrlProfile["JUMP"])) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::JUMP;
				if (ctrl->ctrlStateMachineInstance->smcCurrTouchUp) {
					ctrl->ctrlPhysicsInstance->phyCurrVel.y = 0.0f;
				}
				else {
					ctrl->ctrlPhysicsInstance->phyCurrVel.y = ctrl->ctrlStateMachineInstance->smcActionSpeed;
				}
			}
			// if not on ground 
			else if (!ctrl->ctrlStateMachineInstance->smcCurrTouchDown) {
				ctrl->ctrlStateMachineInstance->smcCurrState = StateMachineComponent::JUMP;
			}

		}
	}
	return;
}