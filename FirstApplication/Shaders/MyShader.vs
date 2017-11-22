#version 330 core
layout (location = 0) in vec3 aPosition; 
layout (location = 1) in vec3 ourColor; 
layout (location = 2) in vec2 texCoord;

out vec4 vertexColor; 
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPosition, 1.0); 
    vertexColor = vec4(ourColor, 1.0f);
	TexCoord = texCoord;
}
