#version 330 core
in vec4 vertexColor;
in vec2 TexCoord;

uniform sampler2D texture0;

out vec4 color;

void main()
{
    color = texture(texture0, TexCoord);
} 
