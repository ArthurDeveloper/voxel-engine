#include "Voxel.h"
#include "Texture.h"
#include "glm/ext/matrix_transform.hpp"

Texture *Voxel::texture = nullptr;
bool Voxel::textureHasBeenInstantiated = false;

Shader *Voxel::shader = nullptr;
bool Voxel::shaderHasBeenInitialized = false;

Voxel::Voxel()
{
	vao.bind();

	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	vbo.bind();
	vbo.bufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	vao.attribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	vao.attribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	initTexture();
	initShader();

	model = glm::mat4(1.0f);
}

void Voxel::update() {
	vao.bind();

	glActiveTexture(GL_TEXTURE0);
	
	texture->bind();
	shader->use();

	GLuint modelLocation = glGetUniformLocation(shader->program(), "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
}

void Voxel::draw() {
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Voxel::setMat4(const char *name, glm::mat4 value) {
	GLuint location = glGetUniformLocation(shader->program(), name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Voxel::translate(float x, float y, float z) {
	glm::vec3 vec = glm::vec3(x, y, z);
	model = glm::translate(model, vec);
}

void Voxel::initTexture() {
	if (!Voxel::textureHasBeenInstantiated) {
		texture = new Texture("res/textures/grass.png");
		texture->bind();
		texture->params();
		texture->build();
		textureHasBeenInstantiated = true;
	}
}

void Voxel::initShader() {
	if (!Voxel::shaderHasBeenInitialized) {
		shader = new Shader();

		shader->fromFile(GL_VERTEX_SHADER, "res/shaders/triangle.vert");
		shader->fromFile(GL_FRAGMENT_SHADER, "res/shaders/triangle.frag");
		shader->link();
	}
}

void Voxel::destroyTexture() {
	delete texture;
}

void Voxel::destroyShader() {
	delete shader;
}