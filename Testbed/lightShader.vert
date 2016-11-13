#version 430 core
in vec4 vPosition;
in vec4 vertexColor;
in vec2 vtexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 myColor;
out vec2 myTexCoord;

void main()
{
	gl_Position = projection * view * model * vPosition;
	myColor = vertexColor;
	myTexCoord = vtexCoord;
}
