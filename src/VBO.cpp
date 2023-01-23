#include "VBO.h"

VBO::VBO() {
    glGenBuffers(1, &id);
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::bufferData(GLenum type, GLsizeiptr size, const void *data, GLenum mode) {
    glBufferData(type, size, data, mode);
}