#include "../inc/components/TransformComponent.h"
#include <iostream>

TransformComponent::TransformComponent() {
	std::cout << "default txf constructed !\n";
	Vector2DSet(&txfPosition, 0, 0);
	Vector2DSet(&txfVelocity, 0.0f, 0.0f);
	Vector2DSet(&txfUpVec, 0.0f, 1.0f);
	Vector2DSet(&txfRightVec, 1.0f, 0.0f);
	txfMaxSpeed = 0.0f;
}

TransformComponent::TransformComponent(float x, float y, float max_speed){
	Vector2DSet(&txfPosition, x, y);
	Vector2DSet(&txfVelocity, 0.0f, 0.0f);
	Vector2DSet(&txfUpVec, 0.0f, 1.0f);
	Vector2DSet(&txfRightVec, 1.0f, 0.0f);
	txfMaxSpeed = max_speed;
}

TransformComponent::~TransformComponent() {

}

void TransformComponent::comInit() {
	txfMaxSpeed = 2.0f;
}

void TransformComponent::comDraw() {

}

void TransformComponent::comUpdate() {

}

void TransformComponent::comHandleEvents() {

}