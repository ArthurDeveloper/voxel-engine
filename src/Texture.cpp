#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(std::string path) {
    glGenTextures(1, &id_);
    imageData = stbi_load(path.c_str(), &width, &height, &channels, 0);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::params() {
    // TODO: Make a method to set those parameters for each texture instead of using hard-coded default
    // values for every texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::build() {
    if (imageData) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Error loading image!" << std::endl;
        throw(errno);
    } 

    stbi_image_free(imageData);
}

GLuint & Texture::id() {
    return id_;
}
