#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


uniform vec3 light_position;
uniform vec3 diffuse_color;
uniform vec3 specular_color;
uniform float shininess;
smooth out vec4 color;
const vec3 vEyeSpaceCameraPosition =  vec3(0,0,0);

void main()
{
		
	color = vec4(1.0f);
	
    gl_Position = projection * view * model * vec4(position, 1.0f);
    TexCoords = texCoords;
	Normal = mat3(transpose(inverse(model))) * normal;
	FragPos = vec3(model) * position;
}
