#pragma once
#include<glm.hpp>
#include "GL\glew.h"
#include "OpenGLRenderer.h"

class BoundingBox
{
public:
	BoundingBox(glm::vec3 &_center);
	BoundingBox();
	~BoundingBox();
public:
	float Xmin, Xmax, Ymin, Ymax, Zmin, Zmax;

	void SetCenter(glm::vec3 &_center);
	void SetScale(glm::vec3 &_scale);
	bool BoxIntersects(const BoundingBox &otherBox);
	void Draw(glm::mat4 transform, OpenGLRenderer* renderer);
private:
	glm::vec3* center;
	glm::vec3 scale;
};

