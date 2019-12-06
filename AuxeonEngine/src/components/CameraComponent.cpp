#include "../inc/components/CameraComponent.h"

CameraComponent::CameraComponent() {
	std::cout << "CameraComponent : created \n";
}

CameraComponent::~CameraComponent() {
	// removing camera objects from GraphicsManager before deleting the component
	
	if (comOwner->gaxComponentExists<CameraComponent>()) {
		GraphicsManager::gfxCreate()->gfxRemoveCam(std::make_pair(comOwner->gaxID, comOwner));
	}
	std::cout << "CameraComponent : destructed \n";
}

void CameraComponent::comInit() {
	// Adding camera objects from GraphicsManager
	if (comOwner->gaxComponentExists<CameraComponent>()) {
		GraphicsManager::gfxCreate()->gfxAddCam(std::make_pair(comOwner->gaxID, comOwner));
	}
}
void CameraComponent::comUpdate() {

}
void CameraComponent::comHandleEvents() {

}
void CameraComponent::comDraw() {

}