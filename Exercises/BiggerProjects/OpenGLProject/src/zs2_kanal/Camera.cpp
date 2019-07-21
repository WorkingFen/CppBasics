#include "Camera.h"
#include <glm\gtx\transform.hpp>


Camera::Camera() : position(1.0f, 0.0f, 2.0f), viewDirection(0.0f, 0.0f, -1.0f), rightDirection(1.0f, 0.0f, 0.0f), UP(0.0f, 1.0f, 0.0f)
{
}

glm::mat4 Camera::getWorldToViewMatrix() const {
	return glm::lookAt(position, position + viewDirection, UP);
}

void Camera::moveForward() {
	position += MOVEMENT_SPEED * viewDirection;
}

void Camera::moveBackward() {
	position += -MOVEMENT_SPEED * viewDirection;
}

void Camera::moveLeft() {
	position += -MOVEMENT_SPEED * rightDirection;
}

void Camera::moveRight() {
	position += MOVEMENT_SPEED * rightDirection;
}
void Camera::moveUp() {
	position += MOVEMENT_SPEED * UP;
}

void Camera::moveDown()	{
	position += -MOVEMENT_SPEED * UP;
}

void Camera::strafeLeft() {
	glm::vec3 strafeDirection = glm::cross(viewDirection, UP);
	glm::vec3 rotateDirection = glm::cross(rightDirection, UP);
	viewDirection += -ROTATION_SPEED * strafeDirection;
	rightDirection += -ROTATION_SPEED * rotateDirection;
}

void Camera::strafeRight() {
	glm::vec3 strafeDirection = glm::cross(viewDirection, UP);
	glm::vec3 rotateDirection = glm::cross(rightDirection, UP);
	viewDirection += ROTATION_SPEED * strafeDirection;
	rightDirection += ROTATION_SPEED * rotateDirection;
}
