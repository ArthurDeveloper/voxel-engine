#pragma once

#include <glad/glad.h>

class VAO {
private:
    GLuint id;

public:
    VAO();

    void bind();
    void attribPointer(
        GLuint index, GLint size, GLenum type, 
        GLboolean normalize, GLsizei stride, const void * offset
    );
};
