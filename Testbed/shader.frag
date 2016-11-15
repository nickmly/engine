#version 430 core

in vec4 inColor;
in vec2 inTexCoord;
in vec3 inNormal;
in vec3 fragPos;

out vec4 fColor;

uniform sampler2D texture;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;	

	vec3 norm = normalize(inNormal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm,lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * vec3(inColor.x,inColor.y,inColor.z);

	fColor = texture2D(texture, inTexCoord) * vec4(result, 1.0f);
}