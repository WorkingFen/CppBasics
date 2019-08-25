#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include "Object.h"

class Ship : public Object
{
public:
	Object *body;
	Object *superstructure;
	Ship(GLuint texture, ShaderProgram *shader);
	void draw(glm::mat4 transformMatrix);
};