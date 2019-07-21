#include "Object.h"
using namespace std;

Object::Object():
	shader(nullptr)
{
	transformation = glm::mat4(1.0);
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
}


Object::Object(std::vector<GLfloat> vertices, std::vector<GLuint> indices, GLuint texture, ShaderProgram *shader) :
	shader(shader)
{

//<<<<<<< HEAD
	this->vertices = std::move(vertices);
	this->indices = std::move(indices);
	this->texture = texture;
//=======
	this->vertices = vertices;
	this->indices = indices;

	printVerticesWithoutNormals();
	printIndices();
	addNormals();
	printVerticesWithNormals();

//>>>>>>> lightNew
	   	  
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(GLfloat), &this->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

	// vertex geometry data
//<<<<<<< HEAD
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex color data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// vertex texture data
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
//=======
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex color data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// vertex normal data
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

//>>>>>>> lightNew

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); //unbind VAO
}
// rysowanie obiektu
void Object::draw(const glm::mat4 transformMatrix) {

	if (texture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->texture);
		glUniform1i(glGetUniformLocation(this->shader->getprogramID(), "Texture0"), 0);
	}

	this->shader->Use();

	glm::mat4 fullTransformMatrix;
	GLint fullTransformMatrixUniformLoc = glGetUniformLocation(this->shader->getprogramID(), "fullTransformMatrix");

	fullTransformMatrix = transformMatrix;

	glUniformMatrix4fv(fullTransformMatrixUniformLoc, 1, GL_FALSE, glm::value_ptr(fullTransformMatrix));

	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	if (texture) glBindTexture(GL_TEXTURE_2D, 0);
}

// metoda do obliczania normalnej z trójk¹ta
glm::vec3 Object::calculateTriangleNormal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) {
	glm::vec3 normal;

	glm::vec3 e1 = v2 - v1;
	glm::vec3 e2 = v3 - v1;

	normal = /*glm::normalize*/(glm::cross(e1, e2));

	return normal;
}

// metoda do dodawania normalnych do wektora
// wektor w klasie powinien nie mieæ normalnych, bo inaczej sie rozwali
// czyli w wektorze atrybutów, wierzcho³ek sk³ada siê z 6 elementów
// na koñcu funkcji, ka¿dy wierzcho³ek powinien mieæ ich ju¿ 8 bo dochodz¹ normalne
void Object::addNormals() {
	vector<GLfloat> newVector;
	glm::vec3 sum, v1,v2,v3;
	int numberOfOccurences = 0;

	cout << "<add normals>" << endl;
	// for every vertex
	for (GLfloat i = 0; i < vertices.size()/6; i++) 
	{

		sum = { 0,0,0 };
		// for every occurence of this vertex in the triangle list
		for (int j = 0; j < indices.size(); j++) 
		{
			if (indices[j] == i) 
			{

				int a, b, c;

				// mamy macierz wierzcho³ków trójk¹ta, np. {1,2,3,    3,1,4      ... )
				// chcê policzyæ normalne dla wierzcho³ka o indexie 1
				// ten wierzcho³ek w jednym trójk¹cie w macierzy jest na pierwszym miejscu, w innym mo¿e byæ na drugim, 
				// dlatego poni¿sza operacja jest potrzebna 
				if (j % 3 == 0) {
					a = j;
					b = j + 1;
					c = j + 2;
				}
				else if ((j+2) % 3 == 0) {
					a = j - 1;
					b = j;
					c = j + 1;
				}
				else if ((j+1) % 3 == 0) {
					a = j - 2;
					b = j - 1;
					c = j;
				}
				
				// tu obliczam normaln¹
				v1 = { vertices[indices[a] * 6] , vertices[indices[a] * 6 + 1], vertices[indices[a] * 6 + 2]};
				v2 = { vertices[indices[b] * 6], vertices[indices[b] * 6 + 1], vertices[indices[b] * 6 + 2]};
				v3 = { vertices[indices[c] * 6], vertices[indices[c] * 6 + 1], vertices[indices[c] * 6 + 2]};
				sum += calculateTriangleNormal(v1,v2,v3);
				numberOfOccurences++;
			}


		}


		//sum /= numberOfOccurences; // mo¿e to te¿ potrzebne?
		//sum = glm::normalize(sum);
		//sum = sum / (float)numberOfOccurences;

		glm::vec3 sum2 = glm::normalize(sum);
		sum = sum2;
		/*
		Fajny komentarz:
		Iterate through all triangles of your mesh. For each vertex of each triangle,
		take the cross product of the two edges the vertex is part of and store it associated to the vertex
		(you'll get several normals for each vertex, because every vertex can be part of several faces).
		Add all normals for each vertex. Normalize. Voila
		*/

		// po policzeniu normalnych, dodaj atrybuty wierzcho³ka razem z normaln¹ do wektora

		// wspó³rzêdne
		newVector.push_back(vertices[6 * i]);
		newVector.push_back(vertices[6 * i + 1]);
		newVector.push_back(vertices[6 * i + 2]);
		// kolor
		newVector.push_back(vertices[6 * i + 3]);
		newVector.push_back(vertices[6 * i + 4]);
		newVector.push_back(vertices[6 * i + 5]);
		// normalne
		newVector.push_back(sum.x);
		newVector.push_back(sum.y);
		newVector.push_back(sum.z);
	}

	// po skoñczeniu iteracji po wszystkich wierzcho³kach, nadpisujê wektor
	vertices = newVector;
	cout << "<added normals>" << endl;



}

// taktyczne couty
void Object::printVerticesWithNormals()
{
	cout << "<vertices attributes with normals" << endl;
	int i=0;
	for (auto it = vertices.begin(); it < vertices.end(); it++)
	{

		if (i % 9 == 0) cout << endl<<i/9<<" ";
		cout << *it << " ";
		i++;

	}
	cout << endl << "<end>" << endl;

}

// taktyczne couty
void Object::printIndices()
{
	cout << "<indices>" << endl;
	int i = 0;
	for (auto it = indices.begin(); it < indices.end(); it++)
	{

		if (i % 3 == 0) cout << endl;
		cout << *it << " ";
		i++;

	}
	cout << endl << "<end>" << endl;

}


// taktyczne couty
void Object::printVerticesWithoutNormals()
{
	cout << "<vertices attributes without normals" << endl;

	int i = 0;
	for (auto it = vertices.begin(); it < vertices.end(); it++)
	{

		if (i % 6 == 0) cout << endl<<i / 6 << " ";
		cout << *it << " ";
		i++;

	}
	cout <<endl<< "<end>" << endl;
}

Object::~Object()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
