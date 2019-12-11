#include "../inc/components/CameraComponent.h"

// Constructor with vectors
CameraComponent::CameraComponent(vec3 position, vec3 up, float yaw, float pitch) : camFront(vec3(0.0f, 0.0f, -1.0f)), camMovementSpeed(CAMSPEED), camMouseSensitivity(CAMSENSITIVITY), camZoom(CAMZOOM) {
	camPosition = position;
	camWorldUp = up;
	camYaw = yaw;
	camPitch = pitch;
	camUpdateCameraVectors();
}

// Constructor with scalar values
CameraComponent::CameraComponent(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : camFront(vec3(0.0f, 0.0f, -1.0f)), camMovementSpeed(CAMSPEED), camMouseSensitivity(CAMSENSITIVITY), camZoom(CAMZOOM) {
	camPosition = vec3(posX, posY, posZ);
	camWorldUp = vec3(upX, upY, upZ);
	camYaw = yaw;
	camPitch = pitch;
	camUpdateCameraVectors();
}

// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
mat4 CameraComponent::camGetViewMatrix() {
	return glm::lookAt(camPosition, camPosition + camFront, camUp);
}
// returns the projection matrix
mat4 CameraComponent::camGetProjMatrix(GLfloat _l, GLfloat _r, GLfloat _b, GLfloat _t, GLfloat _n, GLfloat _f) {
	//return glm::ortho(_l,_r,_b,_t,_n,_f);
	return glm::ortho(0.0f, (float)SCREEN_WIDTH, 0.0f, (float)SCREEN_HEIGHT, -1000.0f, 1000.0f);
	//return glm::perspective(45.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, _n, _f);
}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void CameraComponent::camProcessKeyboard(CameraMovement direction, float deltaTime) {
	float velocity = camMovementSpeed * deltaTime;
	if (direction == CAMFORWARD)
		camPosition += camFront * velocity;
	if (direction == CAMBACKWARD)
		camPosition -= camFront * velocity;
	if (direction == CAMLEFT)
		camPosition -= camRight * velocity;
	if (direction == CAMRIGHT)
		camPosition += camRight * velocity;
}

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void CameraComponent::camProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
	xoffset *= camMouseSensitivity;
	yoffset *= camMouseSensitivity;

	camYaw += xoffset;
	camPitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (camPitch > 89.0f)
			camPitch = 89.0f;
		if (camPitch < -89.0f)
			camPitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Euler angles
	camUpdateCameraVectors();
}

// Calculates the front vector from the Camera's (updated) Euler Angles
void CameraComponent::camUpdateCameraVectors() {
	// Calculate the new Front vector
	vec3 front;
	front.x = cos(glm::radians(camYaw)) * cos(glm::radians(camPitch));
	front.y = sin(glm::radians(camPitch));
	front.z = sin(glm::radians(camYaw)) * cos(glm::radians(camPitch));
	camFront = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	camRight = glm::normalize(glm::cross(camFront, camWorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	camUp = glm::normalize(glm::cross(camRight, camFront));
}

// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void CameraComponent::camProcessMouseScroll(float yoffset) {
	if (camZoom >= 1.0f && camZoom <= 45.0f)
		camZoom -= yoffset;
	if (camZoom <= 1.0f)
		camZoom = 1.0f;
	if (camZoom >= 45.0f)
		camZoom = 45.0f;
}


CameraComponent::~CameraComponent() {
	// removing camera objects from GraphicsManager before deleting the component
	std::cout << "CameraComponent : destructed \n";
	if (comOwner->gaxComponentExists<CameraComponent>()) {
		GraphicsManager::gfxCreate()->gfxRemoveCam(std::make_pair(comOwner->gaxID, comOwner));
	}
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

mat4 CameraComponent::camTestortho(float r, float l, float t, float b, float f, float n) {
	mat4 M;

	// set OpenGL perspective projection matrix
	M[0][0] = 2 / (r - l);
	M[0][1] = 0;
	M[0][2] = 0;
	M[0][3] = 0;

	M[1][0] = 0;
	M[1][1] = 2 / (t - b);
	M[1][2] = 0;
	M[1][3] = 0;

	M[2][0] = 0;
	M[2][1] = 0;
	M[2][2] = -2 / (f - n);
	M[2][3] = 0;

	M[3][0] = -(r + l) / (r - l);
	M[3][1] = -(t + b) / (t - b);
	M[3][2] = -(f + n) / (f - n);
	M[3][3] = 1;

	return M;
}