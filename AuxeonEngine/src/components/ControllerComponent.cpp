#include "../inc/components/ControllerComponent.h"

ControllerComponent::ControllerComponent(int inputProfile) {

	ctrlInputManager = InputManager::inmCreate();
	ctrlFrameRateManager = FrameRateManager::fpsCreate();

	ctrlProfile = ctrlInputManager->inmGetProfile(inputProfile);
	std::cout << "ControllerComponent : created \n";
}

ControllerComponent::~ControllerComponent() {
	std::cout << "ControllerComponent : destructed \n";
}

void ControllerComponent::comInit() {

}

void ControllerComponent::comUpdate() {
	
	if (!comOwner->gaxComponentExists<TransformComponent>()) {
		return;
	}

	float speed = comOwner->gaxGetComponent<TransformComponent>().txfMaxSpeed;
	float dt = ctrlFrameRateManager->fpsGetDeltaTime();

	// movement controls 
	if (ctrlInputManager->inmIsKeyPressed(ctrlProfile["UP"])) {
		comOwner->gaxGetComponent<TransformComponent>().txfPosition.y += dt*speed;
		comOwner->gaxGetComponent<ModelComponent>().modTranslate = glm::translate(comOwner->gaxGetComponent<ModelComponent>().modTranslate, glm::vec3(0, dt*speed, 0));
	}
	if (ctrlInputManager->inmIsKeyPressed(ctrlProfile["DOWN"])) {
		comOwner->gaxGetComponent<TransformComponent>().txfPosition.y -= dt*speed;
		comOwner->gaxGetComponent<ModelComponent>().modTranslate = glm::translate(comOwner->gaxGetComponent<ModelComponent>().modTranslate, glm::vec3(0, -dt*speed, 0));
	}
	if (ctrlInputManager->inmIsKeyPressed(ctrlProfile["LEFT"])) {
		comOwner->gaxGetComponent<TransformComponent>().txfPosition.x -= dt*speed;
		comOwner->gaxGetComponent<ModelComponent>().modTranslate = glm::translate(comOwner->gaxGetComponent<ModelComponent>().modTranslate, glm::vec3(-dt*speed, 0, 0));
	}
	if (ctrlInputManager->inmIsKeyPressed(ctrlProfile["RIGHT"])) {
		comOwner->gaxGetComponent<TransformComponent>().txfPosition.x += dt*speed;
		comOwner->gaxGetComponent<ModelComponent>().modTranslate = glm::translate(comOwner->gaxGetComponent<ModelComponent>().modTranslate, glm::vec3(dt*speed, 0, 0));
	}
	if (ctrlInputManager->inmIsKeyPressed(ctrlProfile["ROT_RIGHT"])) {
		comOwner->gaxGetComponent<ModelComponent>().modRotate = glm::rotate(comOwner->gaxGetComponent<ModelComponent>().modRotate, glm::radians(-0.1f), glm::vec3(0, 0, 1));
	}
	if (ctrlInputManager->inmIsKeyPressed(ctrlProfile["ROT_LEFT"])) {
		comOwner->gaxGetComponent<ModelComponent>().modRotate = glm::rotate(comOwner->gaxGetComponent<ModelComponent>().modRotate, glm::radians(0.1f), glm::vec3(0, 0, 1));
	}
	if (ctrlInputManager->inmIsKeyTriggered(ctrlProfile["TEXTURE_TOGGLE"]) ){
		std::cout << "space pressed" << std::endl;
		comOwner->gaxGetComponent<ModelComponent>().mode = (comOwner->gaxGetComponent<ModelComponent>().mode+1)%2;
	}

}

void ControllerComponent::comDraw() {

}

void ControllerComponent::comHandleEvents() {

}