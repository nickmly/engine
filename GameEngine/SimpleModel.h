#pragma once
#include <glm.hpp>
#include <vector>
#include "Vertex.h"
#include "OpenGLRenderer.h"

using namespace std;
class SimpleModel
{
private:
	vector<Vertex> vertices;
	bool colors = false;
	bool normals = false;
	bool textures = false;
	OpenGLRenderer* renderer;
public:
	SimpleModel(vector<Vertex> _vert, OpenGLRenderer &_rend);
	SimpleModel();
	~SimpleModel();
	void RenderModel();
	void AddComponent(Vertex::VertexType type);
	void AddVertices(vector<Vertex> _vert);
	glm::mat4 transform;
	glm::vec3 movement;
};

