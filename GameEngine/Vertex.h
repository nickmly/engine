#pragma once
#include <glm.hpp>
class Vertex
{
public:
	enum VertexType {
		POSITION,
		COLOR,
		NORMAL,
		TEXTURE
	};
	VertexType type;
	glm::vec4 values;
	Vertex(glm::vec4 _values, VertexType _type);
	Vertex(float x,float y, float z, float w);
	Vertex(float x, float y, float z, float w, VertexType _type);
	~Vertex();
};

