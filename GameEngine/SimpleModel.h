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
	std::vector<glm::vec3> vertPos;
	std::vector<glm::vec3> vertColor;
	std::vector<glm::vec2> vertUV;

	GLuint buffers[3];
	GLuint VAO;

	bool colors = false;
	bool normals = false;
	bool textures = false;
	OpenGLRenderer* renderer;
	glm::mat4 transform;
	glm::vec3 scale;
	GLuint currentTexture;
	Shader shader;
public:
	SimpleModel(vector<Vertex> _vert, OpenGLRenderer &_rend, const char* _textureFile, char* _vertShader, char* _fragShader);
	SimpleModel();
	~SimpleModel();
	void RenderModel();
	void AddComponent(Vertex::VertexType type);
	void AddVertices(vector<Vertex> _vert);
	void SetTransform(glm::mat4 _transform);
	void SetScale(glm::vec3 _scale);
	//Generate buffers and load all vertex positions, colors, and texture coordinates into the vertex array
	void SimpleModel::AssignVertices(std::vector<Vertex> _vertices);
	glm::vec3 GetScale();
};

