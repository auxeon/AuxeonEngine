#include "../inc/components/ColliderComponent.h"	


//helpers
bool getCollision(const Box& box1, const Box& box2);
bool getSeparatingPlane(const vec3& RPos, const vec3& Plane, const Box& box1, const Box& box2);

// collision types
void CollisionTypes::OBBCollide(Box* a, Box* b) {
	if (getCollision(*a, *b)) {
		std::cout << "ColllisionComponent : collide \n";
	}
	else {
		std::cout << "ColllisionComponent : not collide \n";
	}
}

bool CollisionTypes::AABBCollide(Box* a, Box* b) {
	if (
		a->boxCenterTransformed.x + a->boxSizeX / 2.0f >= b->boxCenterTransformed.x - b->boxSizeX / 2.0f &&
		b->boxCenterTransformed.x + b->boxSizeX / 2.0f >= a->boxCenterTransformed.x - a->boxSizeX / 2.0f &&

		a->boxCenterTransformed.y + a->boxSizeY / 2.0f >= b->boxCenterTransformed.y - b->boxSizeY / 2.0f &&
		b->boxCenterTransformed.y + b->boxSizeY / 2.0f >= a->boxCenterTransformed.y - a->boxSizeY / 2.0f
		) {
		return true;
	}
	return false;
}

void CollisionTypes::SphereOBBCollide(Sphere* a, Box* b) {
}


// Box class implementations
Box::Box(vec3 _center, float32 _x_size, float32 _y_size, mat4 _mat) : boxCenter(_center), boxCenterTransformed(_center), boxSizeX(_x_size), boxSizeY(_y_size), boxTransform(_mat) {
	this->shapeID = getShapeType<Box>();

	boxVerticesOriginal.push_back(vec3((_x_size / 2.0f), (_y_size / 2.0f), 0.0f));
	boxVerticesOriginal.push_back(vec3((_x_size / 2.0f), (-_y_size / 2.0f), 0.0f));
	boxVerticesOriginal.push_back(vec3((-_x_size / 2.0f), (-_y_size / 2.0f), 0.0f));
	boxVerticesOriginal.push_back(vec3((-_x_size / 2.0f), (_y_size / 2.0f), 0.0f));
	//for (auto& v : boxVerticesOriginal) {
	//	std::cout <<"x : "<< v.x<<", y : "<<v.y<<", z : " <<v.z;
	//	std::cout << std::endl;
	//}
	std::cout << std::endl;
	boxVerticesTransformed = boxVerticesOriginal;
	boxSizeX = _x_size;
	boxSizeY = _y_size;
	boxSizeZ = 0.0f;

}

Box::~Box() {

}

void Box::shapeAccept(Box* b) {
	return CollisionTypes::OBBCollide(this, b);
}

void Box::shapeAccept(Sphere* b) {
	return CollisionTypes::SphereOBBCollide(b, this);
}

vec3vec Box::shapeGetVertices() {
	return boxVerticesTransformed;
}

void Box::shapeSetVertices(vec3vec _vertices) {
	boxVerticesOriginal = _vertices;
	boxVerticesTransformed = _vertices;
}

void Box::shapeSetTransform(mat4 _mat) {
	boxTransform = _mat;
	boxCenterTransformed = vec3(_mat * vec4(boxCenter, 1.0f));
	if (!boxVerticesOriginal.empty()) {
		// transforming vertices
		for (int i = 0; i < boxVerticesOriginal.size(); ++i) {
			boxVerticesTransformed[i] = vec3(boxTransform * vec4(boxVerticesOriginal[i], 1.0f));
		}
		// transforming normals
		for (int i = 0; i < boxNormsOriginal.size(); ++i) {
			boxNormsTransformed[i] = vec3(boxTransform * vec4(boxNormsOriginal[i], 1.0f));
		}
	}
}

mat4 Box::shapeGetTransform() {
	return boxTransform;
}

// Collision class initializing values 
template <typename T>
void ColliderComponent<T>::comInit() {
	collShape->shapeSetTransform(comOwner->gaxGetComponent<TransformComponent>().txfTransform);
}

// Collision class updating values 
template <typename T>
void ColliderComponent<T>::comUpdate() {
	//std::cout << "collshape : " << collShape << std::endl;
	collShape->shapeSetTransform(comOwner->gaxGetComponent<TransformComponent>().txfTransform);

	//for (int c = 0; c < 4;++c) {
	//	for (int d = 0; d < 4;++d) {
	//		std::cout<<comOwner->gaxGetComponent<TransformComponent>().txfTransform[c][d] << " ";
	//	}
	//	std::cout << "\n";
	//}

	//for (auto& v : collShape->boxVerticesTransformed) {
	//	std::cout << "x : " << v.x << ", y : " << v.y << ", z : " << v.z;
	//	std::cout << std::endl;
	//}
	//std::cout << "updated ! ";
}

//collision class drawing stuff

void ColliderComponent<Box>::comDraw() {


	float32 vertices[32];

	vertices[0] = collShape->boxVerticesOriginal[0][0]; vertices[1] = collShape->boxVerticesOriginal[0][1]; vertices[2] = collShape->boxVerticesOriginal[0][2]; vertices[3] = 0.0f; vertices[4] = 1.0f; vertices[5] = 0.0f; // top right
	vertices[8] = collShape->boxVerticesOriginal[1][0]; vertices[9] = collShape->boxVerticesOriginal[1][1]; vertices[10] = collShape->boxVerticesOriginal[1][2]; vertices[11] = 0.0f; vertices[12] = 1.0f; vertices[13] = 0.0f; // bottom right
	vertices[16] = collShape->boxVerticesOriginal[2][0]; vertices[17] = collShape->boxVerticesOriginal[2][1]; vertices[18] = collShape->boxVerticesOriginal[2][2]; vertices[19] = 0.0f; vertices[20] = 1.0f; vertices[21] = 0.0f; // bottom left
	vertices[24] = collShape->boxVerticesOriginal[3][0]; vertices[25] = collShape->boxVerticesOriginal[3][1]; vertices[26] = collShape->boxVerticesOriginal[3][2]; vertices[27] = 0.0f; vertices[28] = 1.0f; vertices[29] = 0.0f; // top left 


	//for (int l = 0; l < 24; l += 6) {
	//	std::cout << "x : " << vertices[l] << ", y : " << vertices[l + 1] << ", z : " << vertices[l + 2];
	//	std::cout << std::endl;
	//}

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);


	if (collGraphicsManager->gfxDebugDraw) {


		// render the triangle
		collShader->use();

		int loc = glGetUniformLocation(collShader->ID, "model");
		glUniformMatrix4fv(loc, 1, GL_FALSE, &collShape->boxTransform[0][0]);

		mat4 view = collGraphicsManager->gfxActiveCamera->gaxGetComponent<CameraComponent>().camGetViewMatrix();
		loc = glGetUniformLocation(collShader->ID,"view");
		glUniformMatrix4fv(loc, 1, GL_FALSE, &view[0][0]);

		mat4 proj = collGraphicsManager->gfxActiveCamera->gaxGetComponent<CameraComponent>().camGetProjMatrix();
		loc = glGetUniformLocation(collShader->ID, "proj");
		glUniformMatrix4fv(loc, 1, GL_FALSE, &proj[0][0]);

		loc = glGetUniformLocation(collShader->ID, "mode");
		glUniform1i(loc, 1);

		loc = glGetUniformLocation(collShader->ID,"debugDrawColor");
		glUniform3fv(loc, 1, &comOwner->gaxDebugDrawColor[0]);

		glBindVertexArray(VAO);

		glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);

		collShader->unuse();
	}

}

// collision class handleevents
template <typename T>
void ColliderComponent<T>::comHandleEvents() {
	//std::cout << "handle events ! ";
}


// specializaions 
void ColliderComponent<Box>::comInit() {

	// for 3d stuff - do later if time permits
	//collShape->boxNormsOriginal.push_back(comOwner->gaxGetComponent<TransformComponent>().txfUpVec);
	//collShape->boxNormsOriginal.push_back(comOwner->gaxGetComponent<TransformComponent>().txfRightVec);
	//collShape->boxNormsOriginal.push_back(comOwner->gaxGetComponent<TransformComponent>().txfRightVec);
	collShape->boxNormsOriginal.push_back(vec3(1.0f, 0.0f, 0.0f));
	collShape->boxNormsOriginal.push_back(vec3(0.0f, 1.0f, 0.0f));
	collShape->boxNormsOriginal.push_back(vec3(0.0f, 0.0f, 1.0f));
	collShape->boxNormsTransformed.push_back(vec3(1.0f, 0.0f, 0.0f));
	collShape->boxNormsTransformed.push_back(vec3(0.0f, 1.0f, 0.0f));
	collShape->boxNormsTransformed.push_back(vec3(0.0f, 0.0f, 1.0f));
	collShape->boxSizeZ = 0.0f;

	collGraphicsManager = GraphicsManager::gfxCreate();
	collShader = new Shader("shaders/vertex/triangle.vertex", "shaders/fragment/triangle.fragment");

}

// box specialized constructor 
ColliderComponent<Box>::ColliderComponent(vec3 _center, float32 _xSize, float32 _ySize, mat4 _mat) {
	collShape = new Box(_center, _xSize, _ySize, _mat);
	//std::cout << "collshape : " << collShape << std::endl;
}


// sphere specialized constrcutor
//ColliderComponent<Sphere>::ColliderComponent(vec3 _center, float32 _radius, mat4 _mat) {
//
//}

template <typename T>
ColliderComponent<T>::~ColliderComponent() {
	delete collShape;
	delete collShader;
}

bool ColliderComponent<Box>::collGenContact(ColliderComponent<Box>& rb) {
	if (CollisionTypes::AABBCollide(this->collShape, rb.collShape)) {
		//std::cout << "Collision !\n";
		return true;
	}
	else {
		//std::cout << "No Collision !\n";
		return false;
	}
	
}

bool ColliderComponent<Box>::collGenContact(ColliderComponent<Sphere>& rb) {
	//if (CollisionTypes::AABBCollide(this->collShape, rb.collShape)) {
	//	return true;
	//}
	return false;
}

bool ColliderComponent<Sphere>::collGenContact(ColliderComponent<Box>& rb) {
	//if (CollisionTypes::AABBCollide(this->collShape, rb.collShape)) {
	//	return true;
	//}
	return false;
}

bool ColliderComponent<Sphere>::collGenContact(ColliderComponent<Sphere>& rb) {
	//if (CollisionTypes::AABBCollide(this->collShape, rb.collShape)) {
	//	return true;
	//}
	return false;
}



//helpers
// test for separating planes in all 15 axes
bool getCollision(const Box& box1, const Box& box2)
{
	static vec3 RPos;
	RPos = box2.boxCenterTransformed - box1.boxCenterTransformed;

	return !(getSeparatingPlane(RPos, box1.boxNormsTransformed[0], box1, box2) ||
		getSeparatingPlane(RPos, box1.boxNormsTransformed[1], box1, box2) ||
		getSeparatingPlane(RPos, box1.boxNormsTransformed[2], box1, box2) ||
		getSeparatingPlane(RPos, box2.boxNormsTransformed[0], box1, box2) ||
		getSeparatingPlane(RPos, box2.boxNormsTransformed[1], box1, box2) ||
		getSeparatingPlane(RPos, box2.boxNormsTransformed[2], box1, box2) ||
		getSeparatingPlane(RPos, glm::cross(box1.boxNormsTransformed[0], box2.boxNormsTransformed[0]), box1, box2) ||
		getSeparatingPlane(RPos, glm::cross(box1.boxNormsTransformed[0], box2.boxNormsTransformed[1]), box1, box2) ||
		getSeparatingPlane(RPos, glm::cross(box1.boxNormsTransformed[0], box2.boxNormsTransformed[2]), box1, box2) ||
		getSeparatingPlane(RPos, glm::cross(box1.boxNormsTransformed[1], box2.boxNormsTransformed[0]), box1, box2) ||
		getSeparatingPlane(RPos, glm::cross(box1.boxNormsTransformed[1], box2.boxNormsTransformed[1]), box1, box2) ||
		getSeparatingPlane(RPos, glm::cross(box1.boxNormsTransformed[1], box2.boxNormsTransformed[2]), box1, box2) ||
		getSeparatingPlane(RPos, glm::cross(box1.boxNormsTransformed[2], box2.boxNormsTransformed[0]), box1, box2) ||
		getSeparatingPlane(RPos, glm::cross(box1.boxNormsTransformed[2], box2.boxNormsTransformed[1]), box1, box2) ||
		getSeparatingPlane(RPos, glm::cross(box1.boxNormsTransformed[2], box2.boxNormsTransformed[2]), box1, box2));
}

bool getSeparatingPlane(const vec3& RPos, const vec3& Plane, const Box& box1, const Box& box2)
{
	return (fabs(glm::dot(RPos, Plane)) >
		(fabs(glm::dot((box1.boxNormsTransformed[0] * box1.boxSizeX / 2.0f), Plane)) +
			fabs(glm::dot((box1.boxNormsTransformed[1] * box1.boxSizeY / 2.0f), Plane)) +
			fabs(glm::dot((box1.boxNormsTransformed[2] * box1.boxSizeZ / 2.0f), Plane)) +
			fabs(glm::dot((box2.boxNormsTransformed[0] * box2.boxSizeX / 2.0f), Plane)) +
			fabs(glm::dot((box2.boxNormsTransformed[1] * box2.boxSizeY / 2.0f), Plane)) +
			fabs(glm::dot((box2.boxNormsTransformed[2] * box2.boxSizeZ / 2.0f), Plane))));
}