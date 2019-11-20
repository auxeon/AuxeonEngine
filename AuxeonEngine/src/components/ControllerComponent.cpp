#include "../inc/components/ControllerComponent.h"

ControllerComponent::ControllerComponent(int inputProfile) {

	ctrlInputManager = InputManager::inmCreate();
	ctrlProfile = ctrlInputManager->inmGetProfile(inputProfile);
}

ControllerComponent::~ControllerComponent() {

}

void ControllerComponent::comInit() {

}

void ControllerComponent::comUpdate() {
	
	if (!comOwner->gaxComponentExists<TransformComponent>()) {
		return;
	}

	// movement controls 
	if (ctrlInputManager->inmIsKeyPressed(ctrlProfile["UP"])) {
		comOwner->gaxGetComponent<TransformComponent>().txfPosition.y -= comOwner->gaxGetComponent<TransformComponent>().txfMaxSpeed;
	}
	if (ctrlInputManager->inmIsKeyPressed(ctrlProfile["DOWN"])) {
		comOwner->gaxGetComponent<TransformComponent>().txfPosition.y += comOwner->gaxGetComponent<TransformComponent>().txfMaxSpeed;
	}
	if (ctrlInputManager->inmIsKeyPressed(ctrlProfile["LEFT"])) {
		comOwner->gaxGetComponent<TransformComponent>().txfPosition.x -= comOwner->gaxGetComponent<TransformComponent>().txfMaxSpeed;
	}
	if (ctrlInputManager->inmIsKeyPressed(ctrlProfile["RIGHT"])) {
		comOwner->gaxGetComponent<TransformComponent>().txfPosition.x += comOwner->gaxGetComponent<TransformComponent>().txfMaxSpeed;
	}
	// battle controls
}

void ControllerComponent::comDraw() {

}

void ControllerComponent::comHandleEvents() {

}