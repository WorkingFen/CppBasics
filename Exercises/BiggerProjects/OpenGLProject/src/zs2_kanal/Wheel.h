#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include "Object.h"

class Wheel : public Object
{
public:
	Object *wall;
	Object *wheel;
	Wheel(GLuint texture, ShaderProgram *shader);
	void generateWheel(ShaderProgram *shader);
	void draw(glm::mat4 transformMatrix);
};