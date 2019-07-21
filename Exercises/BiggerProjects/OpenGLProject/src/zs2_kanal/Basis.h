#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include "Object.h"

class Basis : public Object
{
public:
	Object *ground;
	Object *canal;
	Basis(GLuint texture1, GLuint texture2, ShaderProgram *shader);
	void draw(glm::mat4 transformMatrix);
};