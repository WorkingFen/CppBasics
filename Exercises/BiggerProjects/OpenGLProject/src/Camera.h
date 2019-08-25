#pragma once

#include <glm\glm.hpp>

#define MOVEMENT_SPEED 0.03f
#define ROTATION_SPEED 0.01f

class Camera
{
	glm::vec3 position;
	glm::vec3 viewDirection;
	glm::vec3 rightDirection;
	const glm::vec3 UP;
	glm::vec2 oldMousePosition;
public:
	Camera();
	glm::mat4 getWorldToViewMatrix() const;

	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void strafeLeft();
	void strafeRight();
};

