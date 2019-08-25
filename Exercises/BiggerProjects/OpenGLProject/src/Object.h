#pragma once

#define GLEW_STATIC

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm\gtx\transform.hpp>
#include <vector>
#include "shprogram.h"

class Object
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::mat4 transformation;
	ShaderProgram *shader;

public:
	GLuint VAO, VBO, EBO;
	GLuint texture;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	Object();
	Object(std::vector<GLfloat> vertices, std::vector<GLuint> indices, GLuint texture, ShaderProgram *shader);
	~Object();

	void draw(const glm::mat4 transformMatrix);


	glm::vec3 calculateTriangleNormal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
	void addNormals();
	void printVerticesWithNormals();
	void printVerticesWithoutNormals();
	void printIndices();
};


