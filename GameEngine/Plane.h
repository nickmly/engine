#pragma once
#include "glm.hpp"
class Plane
{
private:
	glm::vec3 point;
	float a, b, c, d;
public:
	Plane();
	Plane(glm::vec3 &p1, glm::vec3 &p2, glm::vec3 &p3);
	glm::vec3 GetNormal();
	float GetDistance();
	float GetSignedDistance(const glm::vec3 &pt);
	Plane& operator=(const Plane &other);
	friend bool operator==(const Plane &a, const Plane &b);
	friend bool operator!=(const Plane &a, const Plane &b);
	~Plane();
};

