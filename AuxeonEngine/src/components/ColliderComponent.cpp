#include "../inc/components/ColliderComponent.h"	




void CollisionTypes::OBBCollide(Box* a, Box* b) {
	
}


Box::Box(vec3 _center, float32 _x_size, float32 _y_size, float32 _z_size) : boxCenter(_center), boxSizeX(_x_size), boxSizeY(_y_size) , boxSizeZ(_z_size) {
	this->shapeID = getShapeType<Box>();

}

void Box::shapeAccept(Box* b) {
		
}

vec3vec Box::shapeGetVertices() {

	return vec3vec();
}

void Box::shapeSetVertices(vec3vec _vertices) {

}

void Box::shapeVisit(Shape* shp) {

}

template <typename T>
float32 ColliderComponent<T>::collGenContact(ColliderComponent rb) {
	this->collshape->shapeVisit(rb.collShape);
}