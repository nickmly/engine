#version 330 core
struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

uniform Light light;
uniform Material material;
uniform sampler2D texture_diffuse1;
uniform vec3 viewPos;

void main()
{
	vec3 ambient = material.ambient * light.ambient;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm,lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);    
	
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

	vec3 result = (ambient + diffuse + specular) * vec3(1.0f);

    color = vec4(texture(texture_diffuse1, TexCoords)) * vec4(result, 1.0f);
}