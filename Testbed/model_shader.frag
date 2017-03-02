#version 330 core
in vec2 TexCoords;
smooth in vec4 color;

out vec4 fColor;
uniform sampler2D texture_diffuse1;

void main()
{
	fColor = vec4(texture(texture_diffuse1, TexCoords)) * color;
}