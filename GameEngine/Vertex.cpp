#include "Vertex.h"

Vertex::Vertex(glm::vec4 _values, VertexType _type)
{
	values = _values;
	type = _type;
}

Vertex::Vertex(float x, float y, float z, float w)
{
	values = glm::vec4(x, y, z, w);
	type = VertexType::POSITION; // Default to position
}

Vertex::Vertex(float x, float y, float z, float w, VertexType _type)
{
	values = glm::vec4(x, y, z, w);
	type = _type;
}


Vertex::~Vertex()
{
}
