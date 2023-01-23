#pragma once

#include <glad/glad.h>

class VBO {
private:
    GLuint id;

public:
    VBO();

    void bind();
    void bufferData(GLenum type, GLsizeiptr size, const void *data, GLenum mode);
};