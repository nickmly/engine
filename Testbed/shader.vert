#version 430 core
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 myColor;
out vec2 myTexCoord;

void main()
{
	gl_Position = projection * view * model * vPosition;
	myColor = vertexColor;
	myTexCoord = texCoord;
}
