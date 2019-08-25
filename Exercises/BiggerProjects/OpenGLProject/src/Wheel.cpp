#include "Wheel.h"

Wheel::Wheel(GLuint texture, ShaderProgram *shader)
{
	std::vector<GLfloat> newVertices = {
		// coordinates				// color			// texture
		2.95f, -0.6f, 0.05f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,		// 0
		2.95f, -0.6f, -0.05f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// 1
		2.95f, -0.4f, 0.05f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,		// 2
		2.95f, -0.4f, -0.05f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,		// 3

		3.05f, -0.6f, 0.05f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,		// 4
		3.05f, -0.6f, -0.05f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// 5
		3.05f, -0.4f, 0.05f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,		// 6
		3.05f, -0.4f, -0.05f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,		// 7

		2.95f, -0.4f, 0.05f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,		// 8
		2.95f, -0.4f, -0.05f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// 9
		3.05f, -0.4f, 0.05f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,		// 10
		3.05f, -0.4f, -0.05f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,		// 11

		2.95f, -0.6f, 0.05f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// 12
		2.95f, -0.4f, 0.05f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,		// 13
		3.05f, -0.6f, 0.05f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,		// 14
		3.05f, -0.4f, 0.05f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,		// 15

		2.95f, -0.6f, -0.05f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,		// 16
		2.95f, -0.4f, -0.05f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,		// 17
		3.05f, -0.6f, -0.05f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// 18
		3.05f, -0.4f, -0.05f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,		// 19
	};

	std::vector<GLuint> newIndices = {
		0, 1, 2,
		1, 2, 3,
		0, 1, 4,
		1, 4, 5,
		12, 13, 14,
		13, 14, 15,
		16, 17, 18,
		17, 18, 19,
		8, 9, 10,
		9, 10, 11,
		4, 5, 6,
		5, 6, 7,
	};

	wall = new Object(newVertices, newIndices, texture, shader);

	generateWheel(shader);
}

void Wheel::generateWheel(ShaderProgram *shader)
{
	std::vector <GLfloat> newVertices;
	std::vector <GLuint> newIndices;
	GLfloat segmentAngle = GLfloat(360 / 16);
	GLfloat currentAngle = 0;
	GLfloat x = 3.05f;
	GLfloat y = -0.4f, tempY;
	GLfloat z;

	z = 0.1f * glm::cos(currentAngle);
	tempY = y + 0.1f * glm::sin(currentAngle);

	// coordinates
	newVertices.push_back(x);
	newVertices.push_back(tempY);
	newVertices.push_back(z);

	// color
	newVertices.push_back(0.0f);
	newVertices.push_back(0.0f);
	newVertices.push_back(1.0f);

	// textures
	newVertices.push_back(0.0f);
	newVertices.push_back(0.0f);

	// coordinates
	newVertices.push_back(x + 0.05f);
	newVertices.push_back(tempY);
	newVertices.push_back(z);

	// color
	newVertices.push_back(0.0f);
	newVertices.push_back(0.0f);
	newVertices.push_back(1.0f);

	// textures
	newVertices.push_back(0.0f);
	newVertices.push_back(0.0f);

	z = 0.09f * glm::cos(currentAngle);
	tempY = y + 0.09f * glm::sin(currentAngle);

	// coordinates
	newVertices.push_back(x);
	newVertices.push_back(tempY);
	newVertices.push_back(z);

	// color
	newVertices.push_back(0.0f);
	newVertices.push_back(0.0f);
	newVertices.push_back(1.0f);

	// textures
	newVertices.push_back(0.0f);
	newVertices.push_back(0.0f);

	// coordinates
	newVertices.push_back(x + 0.05f);
	newVertices.push_back(tempY);
	newVertices.push_back(z);

	// color
	newVertices.push_back(0.0f);
	newVertices.push_back(0.0f);
	newVertices.push_back(1.0f);

	// textures
	newVertices.push_back(0.0f);
	newVertices.push_back(0.0f);

	currentAngle += segmentAngle;

	for (int i = 0; i < 16; i++)
	{
		z = 0.1f * glm::cos(currentAngle);
		tempY = y + 0.1f * glm::sin(currentAngle);

		// coordinates
		newVertices.push_back(x);
		newVertices.push_back(tempY);
		newVertices.push_back(z);

		// color
		newVertices.push_back(0.0f);
		newVertices.push_back(0.0f);
		newVertices.push_back(1.0f);

		// textures
		newVertices.push_back(0.0f);
		newVertices.push_back(0.0f);

		// coordinates
		newVertices.push_back(x + 0.05f);
		newVertices.push_back(tempY);
		newVertices.push_back(z);

		// color
		newVertices.push_back(0.0f);
		newVertices.push_back(0.0f);
		newVertices.push_back(1.0f);

		// textures
		newVertices.push_back(0.0f);
		newVertices.push_back(0.0f);

		z = 0.09f * glm::cos(currentAngle);
		tempY = y + 0.09f * glm::sin(currentAngle);

		// coordinates
		newVertices.push_back(x);
		newVertices.push_back(tempY);
		newVertices.push_back(z);

		// color
		newVertices.push_back(0.0f);
		newVertices.push_back(0.0f);
		newVertices.push_back(1.0f);

		// textures
		newVertices.push_back(0.0f);
		newVertices.push_back(0.0f);

		// coordinates
		newVertices.push_back(x + 0.05f);
		newVertices.push_back(tempY);
		newVertices.push_back(z);

		// color
		newVertices.push_back(0.0f);
		newVertices.push_back(0.0f);
		newVertices.push_back(1.0f);

		// textures
		newVertices.push_back(0.0f);
		newVertices.push_back(0.0f);

		newIndices.push_back((newVertices.size() / 8) - 8);
		newIndices.push_back((newVertices.size() / 8) - 6);
		newIndices.push_back((newVertices.size() / 8) - 4);

		newIndices.push_back((newVertices.size() / 8) - 6);
		newIndices.push_back((newVertices.size() / 8) - 4);
		newIndices.push_back((newVertices.size() / 8) - 2);

		newIndices.push_back((newVertices.size() / 8) - 7);
		newIndices.push_back((newVertices.size() / 8) - 5);
		newIndices.push_back((newVertices.size() / 8) - 3);

		newIndices.push_back((newVertices.size() / 8) - 5);
		newIndices.push_back((newVertices.size() / 8) - 3);
		newIndices.push_back((newVertices.size() / 8) - 1);

		newIndices.push_back((newVertices.size() / 8) - 8);
		newIndices.push_back((newVertices.size() / 8) - 7);
		newIndices.push_back((newVertices.size() / 8) - 4);

		newIndices.push_back((newVertices.size() / 8) - 7);
		newIndices.push_back((newVertices.size() / 8) - 4);
		newIndices.push_back((newVertices.size() / 8) - 3);

		newIndices.push_back((newVertices.size() / 8) - 6);
		newIndices.push_back((newVertices.size() / 8) - 5);
		newIndices.push_back((newVertices.size() / 8) - 2);

		newIndices.push_back((newVertices.size() / 8) - 5);
		newIndices.push_back((newVertices.size() / 8) - 2);
		newIndices.push_back((newVertices.size() / 8) - 1);

		currentAngle += segmentAngle;
	}

	int init_vert_num = newVertices.size() / 8;
	currentAngle = 0;

	for (int i = 0; i < 16; i++)
	{
		z = 0.01f * glm::cos(currentAngle);
		tempY = y + 0.01f * glm::sin(currentAngle);

		// coordinates
		newVertices.push_back(x);
		newVertices.push_back(tempY);
		newVertices.push_back(z);

		// color
		newVertices.push_back(0.0f);
		newVertices.push_back(0.0f);
		newVertices.push_back(1.0f);

		// textures
		newVertices.push_back(0.0f);
		newVertices.push_back(0.0f);

		// coordinates
		newVertices.push_back(x + 0.05f);
		newVertices.push_back(tempY);
		newVertices.push_back(z);

		// color
		newVertices.push_back(0.0f);
		newVertices.push_back(0.0f);
		newVertices.push_back(1.0f);

		// textures
		newVertices.push_back(0.0f);
		newVertices.push_back(0.0f);

		currentAngle += segmentAngle;
	}

	for (int j = init_vert_num; j < 32 + init_vert_num; j++)
	{
		for (int k = init_vert_num; k < 32 + init_vert_num; k++)
		{
			for (int l = init_vert_num; l < 32 + init_vert_num; l++)
			{
				newIndices.push_back(j);
				newIndices.push_back(k);
				newIndices.push_back(l);
			}
		}
	}

	wheel = new Object(newVertices, newIndices, NULL, shader);
}

void Wheel::draw(glm::mat4 transformMatrix) 
{
	this->wall->draw(transformMatrix);
	this->wheel->draw(transformMatrix);
}