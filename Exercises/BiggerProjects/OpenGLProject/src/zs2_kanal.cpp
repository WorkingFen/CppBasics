#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include <fstream>
#include "Camera.h"
#include "Basis.h"
#include "Platform.h"
#include "Wheel.h"
#include "Ship.h"
#include "Tracks.h"
#include "Tree.h"

//Merge conflicts:     zs2_kanal.cpp; VertexShaderCode.vert; Object.cpp; FragmentShaderCode.frag

using namespace std;

const GLuint WIDTH = 1280, HEIGHT = 720;
Camera camera;

int left_arrow = 0, right_arrow = 0, first_loop = 1;
bool w_key = false, s_key = false, a_key = false, d_key = false, q_key = false, e_key = false, r_key = false, f_key = false;
GLfloat current_ambient = 0.5f;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		left_arrow = 1;
	}
	else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		right_arrow = 1;

	}
	
	if (key == GLFW_KEY_W && action == GLFW_PRESS) w_key = true;
	if (key == GLFW_KEY_S && action == GLFW_PRESS) s_key = true;
	if (key == GLFW_KEY_A && action == GLFW_PRESS) a_key = true;
	if (key == GLFW_KEY_D && action == GLFW_PRESS) d_key = true;
	if (key == GLFW_KEY_Q && action == GLFW_PRESS) q_key = true;
	if (key == GLFW_KEY_E && action == GLFW_PRESS) e_key = true;
	if (key == GLFW_KEY_R && action == GLFW_PRESS) r_key = true;
	if (key == GLFW_KEY_F && action == GLFW_PRESS) f_key = true;

	if (key == GLFW_KEY_W && action == GLFW_RELEASE) w_key = false;
	if (key == GLFW_KEY_S && action == GLFW_RELEASE) s_key = false;
	if (key == GLFW_KEY_A && action == GLFW_RELEASE) a_key = false;
	if (key == GLFW_KEY_D && action == GLFW_RELEASE) d_key = false;
	if (key == GLFW_KEY_Q && action == GLFW_RELEASE) q_key = false;
	if (key == GLFW_KEY_E && action == GLFW_RELEASE) e_key = false;
	if (key == GLFW_KEY_R && action == GLFW_RELEASE) r_key = false;
	if (key == GLFW_KEY_F && action == GLFW_RELEASE) f_key = false;
}

GLuint LoadMipmapTexture(GLuint texId, const char* fname)
{
	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw exception("Failed to load texture file");

	GLuint texture;
	glGenTextures(1, &texture);

	glActiveTexture(texId);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

ostream& operator<<(ostream& os, const glm::mat4& mx)
{
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
			cout << mx[row][col] << ' ';
		cout << endl;
	}
	return os;
}


void setAmbient(ShaderProgram &shader, float ambientStrength) {
	shader.setFloat("ambientStrength", ambientStrength);
}



void incAmbient(ShaderProgram &shader)
{
	GLfloat params[20];
	shader.getFloat("ambientStrength", params);
	cout << params[0] << endl;;
	GLfloat newAmbient = params[0] + 0.05f;

	setAmbient(shader, newAmbient);
	current_ambient = newAmbient;
}

void decAmbient(ShaderProgram &shader)
{
	GLfloat params[20];
	shader.getFloat("ambientStrength", params);
	cout << params[0] << endl;
	GLfloat newAmbient = params[0] - 0.05f;
	if (newAmbient < 0) return;
	setAmbient(shader, newAmbient);
	current_ambient = newAmbient;
}

// lighting
glm::vec3 lightPos(-10.0f, 1.0f, 10.0f);

int main()
{
	if (glfwInit() != GL_TRUE)
	{
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try
	{
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "ZS2 - Kanal", nullptr, nullptr);
		if (window == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glViewport(0, 0, WIDTH, HEIGHT);

		glEnable(GL_DEPTH_TEST);

		

		// Let's check what are maximum parameters counts
		GLint nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		cout << "Max vertex attributes allowed: " << nrAttributes << std::endl;
		glGetIntegerv(GL_MAX_TEXTURE_COORDS, &nrAttributes);
		cout << "Max texture coords allowed: " << nrAttributes << std::endl;

		// Build, compile and link shader program
		ShaderProgram theProgram("VertexShaderCode.vert", "FragmentShaderCode.frag");

		/*
		@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		@@ musia³em utworzyæ klase z wierzcho³kami i krawêdziami @@
		@@ bo mi krzycza³ ¿e by³y redefiniowane	:DDDDD			 @@
		@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		*/

		/*Models models;

		Object ship(models.shipVertices, models.shipIndices, &theProgram);
		Object cabin(models.cabinVertices, models.cabinIndices, &theProgram);
		Object platformL(models.platformLeftVertices, models.platformLeftIndices, &theProgram);
		Object platformR(models.platformRightVertices, models.platformRightIndices, &theProgram);
		Object trackLeft(models.trackLeftVertices, models.trackLeftIndices, &theProgram);
		Object trackRight(models.trackRightVertices, models.trackRightIndices, &theProgram);
		Object ground(models.groundVertices, models.groundIndices, &theProgram);
		Object canal(models.canalVertices, models.canalIndices, &theProgram);
		//Tree tree(0.025f, 0.4f, 1.0f, 36, 36, glm::vec3(1.0f,0.0f,0.0f),glm::vec3(1.0f, 0.0f, 0.0f), &theProgram);

//<<<<<<< HEAD
		Object test(models.shipVertices, models.shipIndices, &theProgram);
		test.printVerticesWithoutNormals();
		test.printIndices();
		test.addNormals();
		test.printVerticesWithNormals();*/
//=======

//>>>>>>> lightNew

		// Set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// prepare textures
		GLuint texture0 = LoadMipmapTexture(GL_TEXTURE0, "cabin.png");
		GLuint texture1 = LoadMipmapTexture(GL_TEXTURE1, "wall.png");
		GLuint texture2 = LoadMipmapTexture(GL_TEXTURE1, "canal2.png");
		GLuint texture3 = LoadMipmapTexture(GL_TEXTURE1, "grass.png");

		Ship ship(texture0, &theProgram);
		Basis basis(texture2, texture3, &theProgram);
		Platform platformL(&theProgram, 'L');
		Platform platformR(&theProgram, 'R');
		Tracks tracksL(&theProgram, 'L');
		Tracks tracksR(&theProgram, 'R');
		Wheel wheel(texture1, &theProgram);
		Tree tree(0.025f, 0.4f, 1.0f, 36, 36, glm::vec3(1.0f,0.0f,0.0f),glm::vec3(1.0f, 0.0f, 0.0f), &theProgram);

		// main event loop
		while (!glfwWindowShouldClose(window))
		{
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();

			// Clear the colorbuffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			static GLfloat perspectiveAngle = 45.0f;

			static GLfloat rotationAngle = 0.0f; // 40.0f;
			static GLfloat xTranslation = 0.0f; //-2.0f
			static GLfloat zTranslation = 0.0f;

//<<<<<<< HEAD
			GLint fullTransformMatrixUniformLoc = glGetUniformLocation(theProgram.getprogramID(), "fullTransformMatrix");
			glm::mat4 fullTransformMatrix;
			glm::mat4 projectionMatrix;
			glm::mat4 translationMatrix;
			glm::mat4 rotationMatrix;

			projectionMatrix = glm::perspective(glm::radians(perspectiveAngle), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
			//glm::mat4 translationMatrix = glm::translate(glm::vec3(xTranslation, 0.3f, zTranslation));
			//glm::mat4 rotationMatrix = glm::rotate(glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
			//fullTransformMatrix = projectionMatrix * translationMatrix * rotationMatrix;


			//glUniformMatrix4fv(fullTransformMatrixUniformLoc, 1, GL_FALSE, &fullTransformMatrix[0][0]);

//=======
			static GLfloat shipXTranslation = -2.0f;
			static GLfloat shipZTranslation = 0.0f;
			static GLfloat shipRotationAngle = 30.0f;
			static bool back = false;
			if (rotationAngle >= 40.0f)  back = true;
			else if (rotationAngle <= -50.0f) back = false;
			if (back) {
				xTranslation += 0.001f;
				zTranslation -= 0.0033f;
				rotationAngle -= 0.1f;
				shipXTranslation -= 0.01f;
				//shipZTranslation -= 0.0033f;
			}
			else {
				xTranslation -= 0.001f;
				zTranslation += 0.0033f;
				rotationAngle += 0.1f;
				//shipXTranslation -= 0.01f;
				//shipZTranslation += 0.0033f;
			}


			glm::mat4 projectionMatrix = glm::perspective(glm::radians(perspectiveAngle), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
			glm::mat4 translationMatrix = glm::translate(glm::vec3(xTranslation, 0.3f, zTranslation));
			glm::mat4 rotationMatrix = glm::rotate(glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));


//>>>>>>> lightNew
			// Draw our first triangle
			theProgram.Use();
			theProgram.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
			if (right_arrow) {
				incAmbient(theProgram);
				right_arrow = 0;
			}
			else if (left_arrow) {
				decAmbient(theProgram);
				left_arrow = 0;
			}
			else setAmbient(theProgram, current_ambient);
			 
			if (w_key) camera.moveForward();
			if (s_key) camera.moveBackward();
			if (a_key) camera.moveLeft();
			if (d_key) camera.moveRight();
			if (q_key) camera.strafeLeft();
			if (e_key) camera.strafeRight();
			if (r_key) camera.moveUp();
			if (f_key) camera.moveDown();

			translationMatrix = glm::translate(glm::vec3(xTranslation, 0.3f, zTranslation));
			rotationMatrix = glm::rotate(glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
			fullTransformMatrix = projectionMatrix * camera.getWorldToViewMatrix() * translationMatrix * rotationMatrix;
			glUniformMatrix4fv(fullTransformMatrixUniformLoc, 1, GL_FALSE, &fullTransformMatrix[0][0]);

			// Drawing objects
//<<<<<<< HEAD
			/*translationMatrix = glm::translate(glm::vec3(shipXTranslation, 0.3f, shipZTranslation));
			rotationMatrix = glm::rotate(glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));*/
//=======
			translationMatrix = glm::translate(glm::vec3(shipXTranslation, 0.3f, shipZTranslation));
			rotationMatrix = glm::rotate(glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
			theProgram.setMat4("projection", projectionMatrix);
			theProgram.setMat4("view", translationMatrix);
			theProgram.setMat4("model",  rotationMatrix);
//>>>>>>> lightNew

			//fullTransformMatrix = projectionMatrix * translationMatrix * rotationMatrix;

			ship.draw(fullTransformMatrix);
			platformL.draw(fullTransformMatrix);
			platformR.draw(fullTransformMatrix);

			//cout << xTranslation << " "<<zTranslation<< endl;

			/*translationMatrix = glm::translate(glm::vec3(xTranslation, 0.3f, zTranslation));
			rotationMatrix = glm::rotate(glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
//<<<<<<< HEAD
			fullTransformMatrix = projectionMatrix * translationMatrix * rotationMatrix;
			glUniformMatrix4fv(fullTransformMatrixUniformLoc, 1, GL_FALSE, &fullTransformMatrix[0][0]);*/
//=======


			trackLeft.draw(projectionMatrix, translationMatrix, rotationMatrix);
			trackRight.draw(projectionMatrix, translationMatrix, rotationMatrix);
			ground.draw(projectionMatrix, translationMatrix, rotationMatrix);
			canal.draw(projectionMatrix, translationMatrix, rotationMatrix);
			//tree.draw(projectionMatrix, translationMatrix, rotationMatrix);
//>>>>>>> lightNew

			tracksL.draw(fullTransformMatrix);
			tracksR.draw(fullTransformMatrix);
			basis.draw(fullTransformMatrix);
			//tree.draw(fullTransformMatrix);
			wheel.draw(fullTransformMatrix);

			// Swap the screen buffers
			glfwSwapBuffers(window);
		}


	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}
