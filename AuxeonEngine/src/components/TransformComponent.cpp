#include "../inc/components/TransformComponent.h"
#include <iostream>

TransformComponent::TransformComponent() {
	std::cout << "default txf constructed !\n";
	// orientation vecs
	txfMaxSpeed = 0.0f;
	txfPosition = vec3(0.0f, 0.0f, 0.0f);
	txfWorldUpVec = vec3(0.0f, 1.0f, 0.0f);
	txfTarget = vec3(0.0f,0.0f,0.0f);
	txfLookVec = glm::normalize(txfTarget - txfPosition);
	txfRightVec = vec3(glm::cross(txfWorldUpVec,txfLookVec));
	txfUpVec = vec3(glm::cross(txfLookVec,txfRightVec));

	txfRotMat = txfScaMat = txfTransform = glm::mat4(1.0f);
	
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

	txfRotMat = txfScaMat = txfTransform = glm::mat4(1.0f);
	
}

TransformComponent::~TransformComponent() {

}

void TransformComponent::comInit() {
	txfTraMat = glm::translate(glm::mat4(1.0f), txfPosition);
}

void TransformComponent::comDraw() {

}

void TransformComponent::comUpdate() {


	txfTraMat = glm::translate(glm::mat4(1.0f), txfPosition);

	// A mult B
	// B*A
	// real order : T mult R mult S : left to right normal math mode
	// OpenGL order : T * (S*R) : right to left pairwise

	txfTransform = comOwner->gaxGetComponent<TransformComponent>().txfTraMat *
				   comOwner->gaxGetComponent<TransformComponent>().txfScaMat *
				   comOwner->gaxGetComponent<TransformComponent>().txfRotMat;


//for (int c = 0; c < 4; ++c) {
//	for (int d = 0; d < 4; ++d) {
//		std::cout << txfTransform[c][d] << " ";
//	}
//	std::cout << std::endl;
//}
//std::cout << "\n";
}

void TransformComponent::comHandleEvents() {

}

void TransformComponent::txfRotate(float _theta) {
}

void TransformComponent::txfTranslate(float _x, float _y) {

}