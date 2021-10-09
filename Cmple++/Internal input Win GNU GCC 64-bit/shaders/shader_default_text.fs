#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 textColor;

void main()
{    
    color = vec4(textColor, 1.0) * vec4(vec3(1.0), texture(image, TexCoords).r);
}