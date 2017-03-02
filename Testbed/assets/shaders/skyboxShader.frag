#version 330 core
in vec3 TexCoords;
in vec4 Normal;
in vec3 Position;
out vec4 color;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{    
    color = texture(skybox, TexCoords);
}