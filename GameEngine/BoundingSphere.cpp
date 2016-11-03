#include "BoundingSphere.h"
//TODO: refactor this entire class
BoundingSphere::BoundingSphere() 
{

}

BoundingSphere::BoundingSphere(glm::vec3 _center, float _radius)
{
	center = _center;
	radius = _radius;
}

glm::vec3 BoundingSphere::GetCenter()
{
	return center;
}

void BoundingSphere::SetCenter(glm::vec3 _center)
{
	center = _center;
}

float BoundingSphere::GetRadius()
{
	return radius;
}

bool BoundingSphere::Intersect(const BoundingSphere & other)
{
	float radiusDist = radius + other.radius;
	float centerDist = (other.center - center).length();
	if (centerDist < radiusDist) {
		return true;
		//return IntersectData(true, centerDist - radiusDist);
	}
	else {
		return false;
		//return IntersectData(false, centerDist - radiusDist);
	}
}
