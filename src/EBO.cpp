#include "EBO.h"

EBO::EBO() {
    glGenBuffers(1, &id);
}

void EBO::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void EBO::bufferData(GLenum type, GLsizeiptr size, const void *data, GLenum mode) {
    glBufferData(type, size, data, mode);
}