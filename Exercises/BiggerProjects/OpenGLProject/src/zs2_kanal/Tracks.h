#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include "Object.h"

class Tracks : public Object
{	
public:
	Object *tracks;
	Tracks(ShaderProgram *shader, char side);
	void draw(glm::mat4 transformMatrix);
};