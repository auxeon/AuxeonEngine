#include "../inc/components/TransformComponent.h"
#include <iostream>

TransformComponent::TransformComponent() {
	
	// orientation vecs
	txfMaxSpeed = 0.0f;
	txfPosition = vec3(0.0f, 0.0f, 0.0f);
	txfWorldUpVec = vec3(0.0f, 1.0f, 0.0f);
	txfTarget = vec3(0.0f,0.0f,0.0f);
	txfLookVec = glm::normalize(txfTarget - txfPosition);
	txfRightVec = vec3(glm::cross(txfWorldUpVec,txfLookVec));
	txfUpVec = vec3(glm::cross(txfLookVec,txfRightVec));
	std::cout << "TransformComponent : created \n";
	
}

TransformComponent::TransformComponent(float x, float y, float max_speed){
	
	// orientation vecs
	txfMaxSpeed = max_speed;
	txfPosition = vec3(x, y, 0.0f);
	txfWorldUpVec = vec3(0.0f, 1.0f, 0.0f);
	txfTarget = vec3(0.0f, 0.0f, 0.0f);
	txfLookVec = glm::normalize(txfTarget - txfPosition);
	txfRightVec = vec3(glm::cross(txfWorldUpVec, txfLookVec));
	txfUpVec = vec3(glm::cross(txfLookVec, txfRightVec));
	std::cout << "TransformComponent : created \n";

}

TransformComponent::~TransformComponent() {
	std::cout << "TransformComponent : destructed \n";
}

void TransformComponent::comInit() {

}

void TransformComponent::comDraw() {

}

void TransformComponent::comUpdate() {

}

void TransformComponent::comHandleEvents() {

}

void TransformComponent::txfRotate(float _theta) {
}

void TransformComponent::txfTranslate(float _x, float _y) {

}