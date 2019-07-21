#pragma once

#define GLEW_STATIC

#include "Object.h"

#pragma once
class Tree
{

	void generateTrunk();
	void generateCrown();
	

public:

	GLfloat trunkRadius;
	GLfloat trunkHeight;
	GLfloat crownRadius;
	GLuint trunkSegments;
	GLuint crownSegments;

	glm::vec3 trunkColor;

	glm::vec3 crownColor;

	Object *crown;
	Object *trunk;
	ShaderProgram *shader;


	Tree();

	Tree(GLfloat trunkRadius, GLfloat trunkHeight,
		GLfloat crownRadius,
		GLuint trunkSegments, GLuint crownSegments, 
		glm::vec3 trunkColor, glm::vec3 crownColor,
		ShaderProgram *shader);

	~Tree();

	void draw(glm::mat4 transformMatrix);


};