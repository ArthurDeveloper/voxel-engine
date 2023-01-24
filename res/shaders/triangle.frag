#version 330 core

in vec3 aColor;
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D aTexture;

void main() {
    FragColor = texture(aTexture, TexCoord);
}