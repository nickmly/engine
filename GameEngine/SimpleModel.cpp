#include "SimpleModel.h"

SimpleModel::SimpleModel(vector<Vertex> _vert, OpenGLRenderer &_rend)
{
	vertices = _vert;
	renderer = &_rend;
	renderer->AssignVertices(vertices);
	movement = glm::vec3(0.0f, 0.0f, 0.0f); //default to 0,0,0
}

SimpleModel::SimpleModel()
{
}


SimpleModel::~SimpleModel()
{
}

void SimpleModel::RenderModel()
{
	renderer->RenderTransform(transform);
	renderer->RenderVertices();
}

void SimpleModel::AddComponent(Vertex::VertexType type)
{
	switch (type) {
	case Vertex::COLOR:
		colors = true;
		break;
	case Vertex::TEXTURE:
		textures = true;
		break;
	case Vertex::NORMAL:
		normals = true;
		break;
	}
}

void SimpleModel::AddVertices(vector<Vertex> _vert)
{
	vertices = _vert;
}

