#version 430 core

in vec4 Color;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 fColor;

uniform sampler2D texture;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;	

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm,lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * vec3(Color.x,Color.y,Color.z);

	fColor = texture2D(texture, TexCoord) * vec4(result, 1.0f);
}