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
    VAO vao;
    VBO vbo;

    glm::mat4 model;

    static Texture *texture;
    static bool textureHasBeenInstantiated;
    static void initTexture();

    static Shader *shader;
    static bool shaderHasBeenInitialized;
    static void initShader();

public:
    Voxel();

    static void destroyTexture();
    static void destroyShader();

    void update();
    void draw();

    void translate(float x, float y, float z);

    void setMat4(const char *name, glm::mat4 value);

};