#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <fstream>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

std::string readFile(std::string path) {
	std::ifstream file;
	file.open(path);

	std::stringstream stream;

	if (file.is_open()) {
		std::string line;
		while (getline(file, line)) {
			stream << line << "\n";
		}
		file.close();
	}

	return stream.str();
}

GLuint compileShader(GLuint type, std::string source) {
	const char *sourceCstr = source.c_str();
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &sourceCstr, NULL);
	glCompileShader(shader);

	int success;
	char errLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, errLog);
		std::cerr << 
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment") << 
			"SHADER COMPILATION ERROR: " 
			<< errLog 
			<< std::endl
		;
	}

	return shader;
}

GLuint createProgram(GLuint vertexShader, GLuint fragmentShader) {
	GLuint program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	int success;
	char errLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, errLog);
		std::cerr << "PROGRAM LINKING ERROR! " << errLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;	
}

int main(void) {
	GLfloat vertices[] = {
		// Coordinates		 // Colors
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
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


	unsigned int VBO;
	glGenBuffers(1, &VBO);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	std::string vertexShaderSource = readFile("res/shaders/triangle.vert");
	std::string fragmentShaderSource = readFile("res/shaders/triangle.frag");

	GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	GLuint shaderProgram = createProgram(vertexShader, fragmentShader);


	while (!glfwWindowShouldClose(window)) {
		glClearColor(0, 120.f/255.f, 255.f/255.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
