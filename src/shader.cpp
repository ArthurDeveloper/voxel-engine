#include "shader.h"

Shader::Shader() {}

void Shader::fromFile(GLuint type, std::string path) {
    std::string source = file::read(path);
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

	if (type == GL_VERTEX_SHADER) {
        vertexShader = shader;
    } else if (type == GL_FRAGMENT_SHADER) {
        fragmentShader = shader;
    }
}

void Shader::link() {
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

	program_ = program;	
}

const GLuint & Shader::program() const {
    return program_;
}