#include "Platform.h"

Platform::Platform(ShaderProgram *shader, char side)
{
	std::vector <GLfloat> newVertices;
	std::vector <GLuint> newIndices = {
		0, 1, 2,
		1, 2, 3,
		0, 1, 4,
		1, 4, 5,
		0, 2, 4,
		2, 4, 6,
		1, 3, 5,
		3, 5, 7,
		2, 3, 6,
		3, 6, 7,
		4, 5, 6,
		5, 6, 7,
	};

	if (side == 'L')
	{
		newVertices = {
			// coordinates			// color			// texture
			-2.4f, 0.53f, 0.4f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// 0
			-2.4f, 0.53f, 0.2f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// 1
			-2.4f, 0.56f, 0.4f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// 2
			-2.4f, 0.56f, 0.2f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// 3
			-2.0f, 0.53f, 0.4f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// 4
			-2.0f, 0.53f, 0.2f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// 5
			-2.0f, 0.56f, 0.4f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// 6
			-2.0f, 0.56f, 0.2f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// 7
		};
	}

	else if (side == 'R')
	{
		newVertices = {
			// coordinates			// color
			0.25f, -0.63f, -0.2f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// 0
			0.25f, -0.63f, -0.4f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// 1
			0.25f, -0.6f, -0.2f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// 2
			0.25f, -0.6f, -0.4f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// 3
			0.75f, -0.63f, -0.2f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// 4
			0.75f, -0.63f, -0.4f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// 5
			0.75f, -0.6f, -0.2f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// 6
			0.75f, -0.6f, -0.4f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		// 7
		};
	}

	generateWheels(newVertices, newIndices, side);
	this->platform = new Object(newVertices, newIndices, NULL, shader);
}

void Platform::generateWheels(std::vector <GLfloat> & newVertices, std::vector <GLuint> & newIndices, char side)
{
	GLfloat segmentAngle = GLfloat(360 / 16);
	GLfloat currentAngle = 0;
	int init_vert_num = newVertices.size() / 8;

	if (side == 'L')
	{
		std::vector <GLfloat> x = { -2.38f, -2.38f, -2.02f, -2.02f };
		std::vector <GLfloat> z = { 0.42f, 0.4f, 0.2f, 0.18f };
		GLfloat tempX;
		GLfloat y = 0.54f, tempY;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				tempX = 0.1f * glm::cos(currentAngle);
				tempY = y + 0.1f * glm::sin(currentAngle);

				// coordinates
				newVertices.push_back(x[i] + tempX);
				newVertices.push_back(tempY);
				newVertices.push_back(z[((2 * i) + 0) % 4]);

				// color
				newVertices.push_back(0.0f);
				newVertices.push_back(0.0f);
				newVertices.push_back(0.0f);

				// textures
				newVertices.push_back(0.0f);
				newVertices.push_back(0.0f);

				// coordinates
				newVertices.push_back(x[i] + tempX);
				newVertices.push_back(tempY);
				newVertices.push_back(z[((2 * i) + 1) % 4]);

				// color
				newVertices.push_back(0.0f);
				newVertices.push_back(0.0f);
				newVertices.push_back(0.0f);

				// textures
				newVertices.push_back(0.0f);
				newVertices.push_back(0.0f);

				currentAngle += segmentAngle;
			}

			for (int k = init_vert_num; k < 32 + init_vert_num; k++)
			{
				for (int l = init_vert_num; l < 32 + init_vert_num; l++)
				{
					for (int m = init_vert_num; m < 32 + init_vert_num; m++)
					{
						newIndices.push_back(k);
						newIndices.push_back(l);
						newIndices.push_back(m);
					}
				}
			}

			currentAngle = 0;
			init_vert_num = newVertices.size() / 8;
		}
	}

	else if (side == 'R')
	{
		std::vector <GLfloat> x = { 0.27, 0.27f, 0.73f, 0.73f };
		std::vector <GLfloat> z = { -0.18f, 0.2f, 0.4f, 0.42f };
		GLfloat tempX;
		GLfloat y = -0.62f, tempY;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				tempX = 0.1f * glm::cos(currentAngle);
				tempY = y + 0.1f * glm::sin(currentAngle);

				// coordinates
				newVertices.push_back(x[i] + tempX);
				newVertices.push_back(tempY);
				newVertices.push_back(z[((2 * i) + 0) % 4]);

				// color
				newVertices.push_back(0.0f);
				newVertices.push_back(0.0f);
				newVertices.push_back(0.0f);

				// textures
				newVertices.push_back(0.0f);
				newVertices.push_back(0.0f);

				// coordinates
				newVertices.push_back(x[i] + tempX);
				newVertices.push_back(tempY);
				newVertices.push_back(z[((2 * i) + 1) % 4]);

				// color
				newVertices.push_back(0.0f);
				newVertices.push_back(0.0f);
				newVertices.push_back(0.0f);

				// textures
				newVertices.push_back(0.0f);
				newVertices.push_back(0.0f);

				currentAngle += segmentAngle;
			}

			for (int k = init_vert_num; k < 32 + init_vert_num; k++)
			{
				for (int l = init_vert_num; l < 32 + init_vert_num; l++)
				{
					for (int m = init_vert_num; m < 32 + init_vert_num; m++)
					{
						newIndices.push_back(k);
						newIndices.push_back(l);
						newIndices.push_back(m);
					}
				}
			}

			currentAngle = 0;
			init_vert_num = newVertices.size() / 8;
		}
	}
}

void Platform::draw(glm::mat4 transformMatrix) 
{
	this->platform->draw(transformMatrix);
}