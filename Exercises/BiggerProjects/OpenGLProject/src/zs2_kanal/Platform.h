#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include "Object.h"

class Platform : public Object
{
public:
	Object *platform;
	Platform(ShaderProgram *shader, char side);
	void generateWheels(std::vector <GLfloat> & newVertices, std::vector <GLuint> & newIndices, char side);
	void draw(glm::mat4 transformMatrix);
};