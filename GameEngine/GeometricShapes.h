#pragma once
#include "Vertex.h"
#include "FileReader.h"
#include <vector>

class GeometricShapes{
public:
	enum SHAPES{
		cube,
		pyramid,
		sphere
	};
	static std::vector<Vertex> GetShape(SHAPES _Shapetype);
};

