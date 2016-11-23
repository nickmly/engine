#pragma once
#include <string>
#include <vector>

#include "Vertex.h"
#include "Shader.h"
#include"GL\glew.h"

using namespace std;

struct Texture {
	GLuint id;
	string type;
};

class Mesh
{
private:
	GLuint VBO[3];
	GLuint VAO, EBO;
	Shader shader;

	//should possibly be pointers
	vector<glm::vec3> vertPos;
	vector<glm::vec2> vertUV;
	vector<glm::vec3> vertNormal;

	//Take all vertices and send them to the correct vectors.
	void ProcessVertices();

	//Load all vertices/uvs/normals into buffers.
	void SetupMesh();
	
	//Draw mesh to screen using a shader.
	void Render();
public:
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	Mesh(vector<Vertex> _vertices, vector<GLuint> _indices, vector<Texture> _textures, char* _vertShader, char* _fragShader);
	~Mesh();
};

