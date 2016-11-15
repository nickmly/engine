#version 430 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec2 vTexCoord;
layout (location = 3) in vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 Color;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
	gl_Position = projection * view * model * vPosition;
	FragPos = vec3(model * vPosition);
	Color = vec4(0.5f, 0.0f, 0.0f, 1.0f);
	TexCoord = vTexCoord;
	Normal = vNormal;
}

