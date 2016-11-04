#pragma once
#include "Vertex.h"
#include <vector>

class GeometricShapes{
public:
	enum SHAPES{
		cube,
		pyramid
	};
	static std::vector<Vertex> GetShape(SHAPES _Shapetype);
};

