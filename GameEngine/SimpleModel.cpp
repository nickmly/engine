#include "SimpleModel.h"

SimpleModel::SimpleModel(vector<Vertex> _vert, OpenGLRenderer &_rend)
{
	vertices = _vert;
	renderer = &_rend;
	renderer->AssignVertices(vertices);
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

void SimpleModel::SetTransform(glm::mat4 _transform)
{
	transform = _transform;
}

