#pragma once
#include "Vertex.h"
#include <vector>
class AbstractRenderer 
{
public:
	enum PrimitiveType {
		TRIANGLE,
		SQUARE
	};
	virtual void RenderPrimitive(PrimitiveType prim) = 0;
	virtual void RenderSimpleModel(std::vector<Vertex> vertices) = 0;
};