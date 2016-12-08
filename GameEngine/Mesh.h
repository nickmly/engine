#pragma once
#include"GL\glew.h"
#include "glm.hpp"
#include <string>
#include <vector>
#include "Shader.h"
#include "OpenGLRenderer.h"

#include "scene.h"

using namespace std;

struct Texture {
	GLuint id;
	string type;
	aiString path;
};

struct mVertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class Mesh
{
private:
	//GLuint VBO[3];
	//GLuint VAO, EBO;
	//Shader shader;

	GLuint VAO, VBO, EBO;

	//should possibly be pointers
	vector<glm::vec3> vertPos;
	vector<glm::vec2> vertUV;
	vector<glm::vec3> vertNormal;

	//Take all vertices and send them to the correct vectors.
	//void ProcessVertices();

	//Load all vertices/uvs/normals into buffers.
	void SetupMesh();
	
	//Draw mesh to screen using a shader.
	
public:
	vector<mVertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	//void SetShader(Shader _shader);
	void Render(Shader shader, OpenGLRenderer rend);

	Mesh(vector<mVertex> _vertices, vector<GLuint> _indices, vector<Texture> _textures);
	~Mesh();
};

