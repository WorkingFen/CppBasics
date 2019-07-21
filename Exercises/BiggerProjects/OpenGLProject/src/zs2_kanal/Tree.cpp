#include "Tree.h"

Tree::Tree() {
}

Tree::Tree(GLfloat trunkRadius, GLfloat trunkHeight,
	GLfloat crownRadius,
	GLuint trunkSegments, GLuint crownSegments,
	glm::vec3 trunkColor, glm::vec3 crownColor,
	ShaderProgram *shader):
	trunkRadius(trunkRadius),
	trunkHeight(trunkHeight),
	crownRadius(crownRadius),
	trunkSegments(trunkSegments),
	crownSegments(crownSegments),
	trunkColor(trunkColor),
	crownColor(crownColor),
	shader(shader)
{
	generateTrunk();
	generateCrown();
}

Tree::~Tree()
{

}


void Tree::generateTrunk() {

	std::vector<GLfloat> trunkVertices;
	std::vector<GLuint> trunkIndices;

	GLfloat segmentAngle = GLfloat(360 / trunkSegments);
	GLfloat currentAngle = 0;
	GLfloat x;
	GLfloat y = this->trunkHeight / 2;
	GLfloat z;

	// top vertices
	for (GLuint i = 0; i < trunkSegments; ++i) {

		x = trunkRadius * glm::cos(currentAngle);
		z = trunkRadius * glm::sin(currentAngle);

		// coordinates
		trunkVertices.push_back(x);
		trunkVertices.push_back(y);
		trunkVertices.push_back(z);

		// color
		trunkVertices.push_back(trunkColor.x);
		trunkVertices.push_back(trunkColor.y);
		trunkVertices.push_back(trunkColor.z);



		currentAngle += segmentAngle;
	}

	currentAngle = 0;

	// bottom vertices
	for (GLuint i = trunkSegments; i < trunkSegments*2; ++i) {

		x = this->trunkRadius * glm::cos(currentAngle);
		z = this->trunkRadius * glm::sin(currentAngle);

		// coordinates
		trunkVertices.push_back(x);
		trunkVertices.push_back(-y);
		trunkVertices.push_back(z);

		// color
		trunkVertices.push_back(trunkColor.x);
		trunkVertices.push_back(trunkColor.y);
		trunkVertices.push_back(trunkColor.z);

		currentAngle += segmentAngle;
	}

	// now triangles
	for (GLuint i = 0; i < trunkSegments; ++i) {

		trunkIndices.push_back(i);
		trunkIndices.push_back(i + trunkSegments);
		trunkIndices.push_back(i + 1);


		trunkIndices.push_back(i + trunkSegments);
		trunkIndices.push_back(i + trunkSegments + 1);
		trunkIndices.push_back(i + 1);

	}

	//taktyczne couty
	/*
	for (GLuint i = 0; i < 2 * trunkSegments* 6; i+=6) {
		cout << "Vertices: v["<<i<<"] = "<<trunkVertices[i] << ", v[" << i+1 << "] = " << trunkVertices[i + 1] <<", v[" << i+2 << "] = " << trunkVertices[i + 2] << endl;
	}*/


	this->trunk = new Object(trunkVertices, trunkIndices, NULL, shader);
}

void Tree::generateCrown() {
	// TODO
}
void Tree::draw(glm::mat4 transformMatrix) {
	this->trunk->draw(transformMatrix);
}