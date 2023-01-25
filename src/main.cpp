#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <glm/ext/matrix_float4x4.hpp>
#include "glm/ext/matrix_clip_space.hpp"
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


int main(void) {
	GLfloat vertices[] = {
		// Coordinates		    // Colors            // Texture
		 0.5f,    0.5f, 0.0f,   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
		 0.5f,   -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
		-0.5f,   -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
		-0.5f,    0.5f, 0.0f,   1.0f, 1.0f, 0.0f,    0.0f, 1.0f,
	};

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

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


	VAO vao;
	VBO vbo;
	EBO ebo;

	vao.bind();

	vbo.bind();
	vbo.bufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	vao.attribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	vao.attribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	vao.attribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

	ebo.bind();
	ebo.bufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	Shader shader;

	shader.fromFile(GL_VERTEX_SHADER, "res/shaders/triangle.vert");
	shader.fromFile(GL_FRAGMENT_SHADER, "res/shaders/triangle.frag");

	shader.link();

	Texture texture("res/textures/grass.png");

	texture.bind();
	texture.params();
	texture.build();
	
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0, 120.f/255.f, 255.f/255.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		texture.bind();

		shader.use();

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(1.0f, 0.0f, -3.0f));
		
		GLuint viewLocation = glGetUniformLocation(shader.program(), "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

		// TODO: Put this outside of the loop to improve performance
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.f), 640.f/480.f, 0.1f, 100.f);

		GLuint projectionLocation = glGetUniformLocation(shader.program(), "projection");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

		vao.bind();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (GLfloat)glfwGetTime()*3, glm::vec3(1.0f, -0.3f, 1.0f));

		GLuint modelLocation = glGetUniformLocation(shader.program(), "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
