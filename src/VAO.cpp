#include "VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &id);
}

void VAO::bind() {
    glBindVertexArray(id);
}

void VAO::attribPointer(
    GLuint index, GLint size, GLenum type,
    GLboolean normalize, GLsizei stride, const void * offset
) {
    glVertexAttribPointer(index, size, type, normalize, stride, offset);
    glEnableVertexAttribArray(index);
}
