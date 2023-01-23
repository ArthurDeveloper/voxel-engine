#pragma once

#include <glad/glad.h>
#include <iostream>
#include "util/file.h"

class Shader {
private:
    GLuint vertexShader, fragmentShader, program_;

public:
    Shader();

    void fromFile(GLuint type, std::string path);
    void link();
    void use();

    const GLuint & program() const;

};