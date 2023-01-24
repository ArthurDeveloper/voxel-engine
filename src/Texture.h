#pragma once

#include <glad/glad.h>
#include <iostream>

class Texture {
private:
    int width, height, channels;
    unsigned char *imageData;
    GLuint id_;

public:
    Texture(std::string path);

    void bind();
    void params();
    void build();
    
    GLuint & id();
};