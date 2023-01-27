#pragma once

#include <glad/glad.h>
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

public:
    Voxel();

    void bindVAO();
    void bindTexture();
   
    void useShader(); 
    GLuint shaderProgram();

};