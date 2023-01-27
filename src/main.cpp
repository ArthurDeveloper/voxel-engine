#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <glm/ext/matrix_float4x4.hpp>
#include "Voxel.h"
#include "glm/ext/matrix_clip_space.hpp"
#include <glm/vec3.hpp>
#include "shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

float pitch = 0.0f;
float yaw = 0.0f;

glm::vec3 direction;
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 viewPosition = glm::vec3(0.0f, 0.0f, -3.0f);

// Relative to mouse
GLfloat lastX = (GLfloat)WINDOW_WIDTH/2, lastY = (GLfloat)WINDOW_HEIGHT/2;
GLfloat sensitivity = 0.1f;

Voxel *voxel;

void handleInputs(GLFWwindow *window);
void mouseCallback(GLFWwindow *window, GLdouble ax, GLdouble ay);

int main(void) {
	if (glfwInit()) {
		std::cout << "Glfw workin'!\n";
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game", nullptr, nullptr);

	if (window == NULL) {
		std::cerr << "Couldn't create window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Error while loading glad." << std::endl;
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	voxel = new Voxel();

	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallback);
	
	while (!glfwWindowShouldClose(window)) {
		handleInputs(window);

		glClearColor(0, 120.f/255.f, 255.f/255.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		voxel->bindTexture();

		voxel->useShader();

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::lookAt(viewPosition, viewPosition + cameraFront, glm::vec3(0.0f, 1.0f, 0.0f));
		
		GLuint viewLocation = glGetUniformLocation(voxel->shaderProgram(), "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

		// TODO: Put this outside of the loop to improve performance
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.f), 640.f/480.f, 0.1f, 100.f);

		GLuint projectionLocation = glGetUniformLocation(voxel->shaderProgram(), "projection");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

		voxel->bindVAO();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (GLfloat)glfwGetTime()*3, glm::vec3(1.0f, -0.3f, 1.0f));

		GLuint modelLocation = glGetUniformLocation(voxel->shaderProgram(), "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();

	delete voxel; 

	return 0;
}

void handleInputs(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_LEFT) || glfwGetKey(window, GLFW_KEY_A)) 
		viewPosition -= 0.1f * glm::normalize(glm::cross(cameraFront, cameraUp));
	if (glfwGetKey(window, GLFW_KEY_RIGHT) || glfwGetKey(window, GLFW_KEY_D)) 
		viewPosition += 0.1f * glm::normalize(glm::cross(cameraFront, cameraUp));
	if (glfwGetKey(window, GLFW_KEY_UP) || glfwGetKey(window, GLFW_KEY_W)) 
		viewPosition += 0.1f * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_DOWN) || glfwGetKey(window, GLFW_KEY_S)) 
		viewPosition -= 0.1f * cameraFront;
}

void mouseCallback(GLFWwindow *window, GLdouble ax, GLdouble ay) {
	float x = static_cast<GLfloat>(ax);
	float y = static_cast<GLfloat>(ay);

	GLfloat xoffset = x - lastX;
	GLfloat yoffset = lastY - y;

	lastX = x;
	lastY = y;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	cameraFront = glm::normalize(direction);

	if (pitch > 90.f) {
		pitch = 90.f;
	} else if (pitch < -90.f) {
		pitch = -90.f;
	}
}