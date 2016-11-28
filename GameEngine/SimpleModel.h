#pragma once
#include <glm.hpp>
#include <vector>
#include "Vertex.h"
#include "Shader.h"
#include "OpenGLRenderer.h"

using namespace std;
class SimpleModel
{
private:
	//should possibly be pointers
	std::vector<glm::vec3> vertPos;
	std::vector<glm::vec3> vertColor;
	std::vector<glm::vec2> vertUV;
	std::vector<glm::vec3> vertNormal;
	glm::mat4 transform;

	GLuint buffers[4];
	GLuint VAO;

	bool colors = false;
	bool normals = false;
	bool textures = false;
	
	OpenGLRenderer* renderer;
	
	GLuint currentTexture;
	Shader shader;

public:

	SimpleModel(vector<Vertex> _vert, OpenGLRenderer &_rend, const char* _textureFile, char* _vertShader, char* _fragShader);
	~SimpleModel();
	
	void RenderModel();
	void AddComponent(Vertex::VertexType type);
	void AddVertices(vector<Vertex> _vert);
	void SetTransform(glm::mat4 _transform) { transform = _transform; }

	//Generate buffers and load all vertex positions, colors, and texture coordinates into the vertex array
	void SimpleModel::AssignVertices(std::vector<Vertex> _vertices);
};

