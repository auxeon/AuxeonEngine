#include "../inc/components/PhysicsComponent.h"

PhysicsComponent::PhysicsComponent() {

	phyGravity = vec3(0.0, 0.0f, 0.0);
	phyInvMass = phyMass = 0.0f;
	phyMass = 1.0f;
	phyCurrForce = phyPrevForce = vec3(0.0f, 0.0f, 0.0f);
	phyCurrAcc = phyPrevAcc = vec3(0.0f, 0.0f, 0.0f);
	phyCurrVel = phyPrevVel = vec3(0.0f, 0.0f, 0.0f);
	phyCurrPos = phyPrevPos = vec3(0.0f, 0.0f, 0.0f);
	phyStateMachineInstance = NULL;

	phyBoxColliderInstance = NULL;
	phySphereColliderInstance = NULL;
	phyTxfInstance = NULL;
	phyCollisionManager = NULL;
	phyFrameRateManager = NULL;

	// managers
	phyCollisionManager = CollisionManager::colmanCreate();
	phyFrameRateManager = FrameRateManager::fpsCreate();

}

PhysicsComponent::~PhysicsComponent() {
}

void PhysicsComponent::comInit() {
	// actively do shit only if the components actuall exist
	// else skip
	if (comOwner->gaxComponentExists<TransformComponent>()) {
		phyTxfInstance = &comOwner->gaxGetComponent<TransformComponent>();
		phyCurrPos = phyPrevPos = phyTxfInstance->txfPosition;
	}
	if (comOwner->gaxComponentExists<ColliderComponent<Box>>()) {
		phyBoxColliderInstance = &comOwner->gaxGetComponent<ColliderComponent<Box>>();
	}
	if (comOwner->gaxComponentExists<ColliderComponent<Sphere>>()) {
		phySphereColliderInstance = &comOwner->gaxGetComponent<ColliderComponent<Sphere>>();
	}
	if (comOwner->gaxComponentExists<StateMachineComponent>()) {
		phyStateMachineInstance = &comOwner->gaxGetComponent<StateMachineComponent>();
	}

	//mass updates
	if (0.0f == phyMass) {
		phyInvMass = 0.0f;
	}
	else {
		phyInvMass = 1 / phyMass;
	}

}

void PhysicsComponent::comUpdate() {



}
void PhysicsComponent::phyIntegrate(float32 _gravity, float32 _dt) {
	float32 dt = _dt;

	// mass 
	//mass updates
	if (0.0f == phyMass) {
		phyInvMass = 0.0f;
	}
	else {
		phyInvMass = 1 / phyMass;
	}


	// store prev data
	phyPrevPos.x = phyCurrPos.x;
	phyPrevPos.y = phyCurrPos.y;
	phyPrevPos.z = phyCurrPos.z;
	// make updates

	phyCurrForce.y -= _gravity;

	// ForceUpdates accelration
	phyCurrAcc.y = phyCurrForce.y * phyInvMass;
	phyCurrAcc.x = phyCurrForce.x * phyInvMass;
	phyCurrAcc.z = phyCurrForce.z * phyInvMass;


	phyCurrVel.x = phyCurrVel.x + phyCurrAcc.x * dt;
	phyCurrVel.y = phyCurrVel.y + phyCurrAcc.y * dt;
	phyCurrVel.z = phyCurrVel.z + phyCurrAcc.z * dt;

	phyCurrForce.x = phyCurrForce.y = phyCurrForce.z = 0.0f;

	phyCurrPos.x = phyCurrPos.x + phyCurrVel.x * dt;
	phyCurrPos.y = phyCurrPos.y + phyCurrVel.y * dt;
	phyCurrPos.z = phyCurrPos.z + phyCurrVel.z * dt;


	// state updates
	if (NULL != phyStateMachineInstance) {
		phyStateMachineInstance->smcPrevTouchRight = phyStateMachineInstance->smcCurrTouchRight;
		phyStateMachineInstance->smcPrevTouchLeft = phyStateMachineInstance->smcCurrTouchLeft;
		phyStateMachineInstance->smcPrevTouchUp = phyStateMachineInstance->smcCurrTouchUp;
		phyStateMachineInstance->smcPrevTouchDown = phyStateMachineInstance->smcCurrTouchDown;
	}

	// push chanes to transform component
	if (phyMass != 0.0f) {
		if (NULL != phyTxfInstance) {
			phyTxfInstance->txfPosition = phyCurrPos;
		}
	}
	else {
		phyCurrPos = phyTxfInstance->txfPosition;
	}

}
void PhysicsComponent::comDraw() {

}
void PhysicsComponent::comHandleEvents() {

}

void PhysicsComponent::testAddVelocity(vec3 _v) {
	phyCurrVel.x = _v.x;
	phyCurrVel.y = _v.y;
	phyCurrVel.z = _v.z;
}
