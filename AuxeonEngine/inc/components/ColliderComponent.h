#pragma once

// helpers
#define GLM_SWIZZLE_XYZW
#include "../libs/GLM-0.9.9.6/glm/glm.hpp"
#include "../libs/GLM-0.9.9.6/glm/gtx/transform.hpp"
#include "../inc/helpers/shader.h"
#include <math.h>
#include<unordered_map>
// entities
#include "../inc/entities/Component.h"
#include "../inc/entities/GameObject.h"
// managers
#include "../inc/managers/FrameRateManager.h"
#include "../inc/managers/GraphicsManager.h"
// components
#include "../inc/components/ModelComponent.h"

#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

using vec3 = glm::vec3;
using float32 = glm::float32;
using ShapeID = std::size_t;
using vec3 = glm::vec3;
//using ContactMap = std::unordered_map<int, GameObject*>;
using vec3vec = std::vector<vec3>;
using mat4 = glm::mat4;


// forward declare all shape type classes here 
class Sphere;
class Box;


class Contact {
	std::pair<GameObject*, GameObject*> goPair;
};


class CollisionTypes {
public:
	static void OBBCollide(Box* a, Box* b);
	static bool AABBCollide(Box* a, Box* b);
	static void SphereOBBCollide(Sphere* a, Box* b);
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
	virtual void shapeSetVertices(vec3vec _vertices) = 0;
	virtual vec3vec shapeGetVertices() = 0;
	virtual void shapeSetTransform(mat4 _mat) = 0;
	virtual mat4 shapeGetTransform() = 0;
	virtual void shapeAccept(Box* _b) = 0;
	virtual void shapeAccept(Sphere* _b) = 0;
};

class Sphere : public Shape {
	int a;
};



class Box : public Shape {

public:

	ShapeID shapeID;
	float32 boxSizeX;
	float32 boxSizeY;
	float32 boxSizeZ;

	vec3vec boxVerticesOriginal;
	vec3vec boxVerticesTransformed;

	vec3vec boxNormsOriginal;
	vec3vec boxNormsTransformed;

	mat4 boxTransform;

	vec3 boxCenter;
	vec3 boxCenterTransformed;

public:

	vec3vec shapeGetVertices();
	void shapeSetVertices(vec3vec _vertices);
	void shapeSetTransform(mat4 _mat);
	mat4 shapeGetTransform();

	void shapeAccept(Box* b);
	void shapeAccept(Sphere* b);

	Box(vec3 _center, float32 _xSize, float32 _ySize, mat4 _mat);
	~Box();
};

template <typename T>
class ColliderComponent : public Component {

public:


	ColliderComponent(vec3 _center, float32 _xSize, float32 _ySize, mat4 _mat);
	~ColliderComponent();

	void comInit();
	void comDraw();
	void comHandleEvents();
	void comUpdate();

	bool collGenContact(ColliderComponent<Box>& rb);
	bool collGenContact(ColliderComponent<Sphere>& rb);

public:
	T* collShape;
	GraphicsManager* collGraphicsManager;
	Shader* collShader;
	vec3 collDebugDrawColor;

};

#endif