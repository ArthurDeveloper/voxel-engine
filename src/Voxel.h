#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "shader.h"

class Voxel {
private:
    GLfloat vertices[5 * 6 * 6];

    VAO vao;
    VBO vbo;
    
    Shader shader;
    Texture texture;

    glm::mat4 model;

public:
    Voxel();

    void update();

    void bindVAO();
    void bindTexture();
   
    void useShader(); 
    GLuint shaderProgram();

};