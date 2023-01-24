#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>
#include <iostream>

class Texture {
private:
    int width, height, channels;
    unsigned char *imageData;
    GLuint texture;

public:
    Texture(std::string path);

    void bind();
    void generate();
};