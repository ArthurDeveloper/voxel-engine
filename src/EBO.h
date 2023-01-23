#pragma once

#include <glad/glad.h>

class EBO {
private:
    GLuint id;

public:
    EBO();

    void bind();
    void bufferData(GLenum type, GLsizeiptr size, const void *data, GLenum mode);
};