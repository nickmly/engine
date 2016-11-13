#version 430 core

in vec4 myColor;
in vec2 myTexCoord;

out vec4 fColor;

uniform sampler2D texture;
uniform vec3 lightColor;

void main()
{
	fColor = texture2D(texture, myTexCoord) * vec4(vec3(myColor.x,myColor.y,myColor.z) * lightColor, 1.0f);
}