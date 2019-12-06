#pragma once

// helpers
#define GLM_SWIZZLE_XYZW
#include "../libs/GLM-0.9.9.6/glm/glm.hpp"
#include "../libs/GLM-0.9.9.6/glm/gtx/transform.hpp"
#include<unordered_map>
// component 
#include "../inc/entities/Component.h"
#include "../inc/entities/GameObject.h"
// managers
#include "../inc/managers/FrameRateManager.h"

#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

using vec3 = glm::vec3;
using float32 = glm::float32;
using ShapeID = std::size_t;
using vec3 = glm::vec3;
using ContactMap = std::unordered_map<int, GameObject*>;
using vec3vec = std::vector<vec3>;
using mat4 = glm::mat4;


// forward declare all shape type classes here 
class Box;


class CollisionTypes {
public:
	void OBBCollide(Box* a, Box* b);
};


// Static component ID helpers
inline ShapeID getShapeID() {
	static ShapeID id = 0;
	return ++id;
}

template<typename T>
ComponentID getShapeType() {
	static ShapeID idType = getShapeID();
	return idType;
}


class Shape {
public:
	ShapeID shapeID;
	vec3vec shapeVerticesOriginal;
	vec3vec shapeVerticesTransformed;
	mat4 shapeTransformMat;

public:
	virtual void shapeAccept(Shape* ) = 0;
	virtual void shapeVisit(Shape* ) = 0;
	virtual void shapeRotate() = 0;
	virtual void shapeScale() = 0;
	virtual void shapeTranslate() = 0;
	virtual void shapeSetVertices() = 0;
	virtual vec3vec shapeGetVertices() = 0;
};

class Box : Shape{

public:
	float32 boxSizeX;
	float32 boxSizeY;
	float32 boxSizeZ;

	vec3vec boxFaceNormsOriginal;
	vec3vec boxFaceNormsTransformed;

	vec3 boxCenter;

public:
	void shapeRotate(float32 theta);
	void shapeScale(float32 Sx, float32 Sy, float32 Sz);
	void shapeTranslate(float32 Tx, float32 Ty, float32 Tz);
	void shapeSetVertices(vec3vec v3v);
	vec3vec shapeGetVertices();

	void shapeAccept(Box* b);
	//void shapeAccept(Circle* shp);
	void shapeVisit(Shape* shp);
	
	Box(vec3 _center, float32 _xSize, float32 _ySize, float32 _zSize);
	~Box();
};

template <typename T>
class ColliderComponent : public Component{
	
public:

	ColliderComponent();
	~ColliderComponent();

	void comInit();
	void comDraw();
	void comHandleEvents();
	void comUpdate();

	float32 collGenContact(ColliderComponent rb);

private:
	T* collShape;

};

#endif