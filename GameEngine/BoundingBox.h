#pragma once
#include<glm.hpp>
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
private:
	glm::vec3* center;
	glm::vec3 scale;
};

