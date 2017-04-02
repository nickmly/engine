#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 light_position;
uniform vec3 diffuse_color;
uniform vec3 specular_color;
uniform float shininess;
smooth out vec4 color;
uniform vec3 vEyeSpaceCameraPosition;
uniform mat3 lightNormal;

void main()
{
	mat4 modelView = view * model;
	//mat3 lightNormal = mat3(transpose(inverse(modelView)));

	vec4 vEyeSpaceLightPosition = (modelView) * vec4(light_position,1.0f);
	vec4 vEyeSpacePosition = (modelView) * vec4(position,1.0f);
	vec3 vEyeSpaceNormal = normalize(lightNormal * normal);
	
	vec3 L = normalize(vEyeSpaceLightPosition.xyz - vEyeSpacePosition.xyz);
	vec3 V = normalize(vEyeSpaceCameraPosition.xyz - vEyeSpacePosition.xyz);
	vec3 H = normalize(L+V);
	
	float diffuse = max(0, dot(vEyeSpaceNormal,L));
	float specular = max(0, pow(dot(vEyeSpaceNormal,H),shininess));
		
	color = diffuse * vec4(diffuse_color, 1.0f) + specular * vec4(specular_color,1.0f);
	
    gl_Position = (projection * modelView) * vec4(position, 1.0f);
    TexCoords = texCoords;
}
