#include "Texture.h"

Texture::Texture(std::string path) {
    imageData = stbi_load(path.c_str(), &width, &height, &channels, 0);

    // TODO: Make a method to set those parameters for each texture instead of using hard-coded default
    // values for every texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenTextures(1, &texture);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::generate() {
    if (imageData) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(imageData);
    } else {
        std::cerr << "Error loading image!" << std::endl;
        throw(errno);
    } 
}  
