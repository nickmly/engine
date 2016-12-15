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
	vec3 N = mat3(transpose(inverse(model))) * normal;
	vec4 vEyeSpaceLightPosition = (model * view) * vec4(light_position,1.0f);
	vec4 vEyeSpacePosition = (model * view) * vec4(position,1.0f);
	vec3 vEyeSpaceNormal = normalize(N * normal);
	
	vec3 L = normalize(vEyeSpaceLightPosition.xyz - vEyeSpacePosition.xyz);
	vec3 V = normalize(vEyeSpaceCameraPosition.xyz - vEyeSpacePosition.xyz);
	vec3 H = normalize(L+V);
	
	float diffuse = max(0, dot(vEyeSpaceNormal,L));
	float specular = max(0, pow(dot(vEyeSpaceNormal,H),shininess));
		
	color = diffuse * vec4(diffuse_color,1.0f) + specular * vec4(specular_color,1.0f);
	
    gl_Position = projection * view * model * vec4(position, 1.0f);
    TexCoords = texCoords;
	Normal = mat3(transpose(inverse(model))) * normal;
	FragPos = vec3(model) * position;
}
