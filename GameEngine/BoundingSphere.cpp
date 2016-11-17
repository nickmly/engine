//#include "BoundingSphere.h"
////TODO: refactor this entire class
//BoundingSphere::BoundingSphere() 
//{
//
//}
//
//BoundingSphere::BoundingSphere(glm::vec3 &_center, float _radius)
//{
//	center = &_center;
//	radius = _radius;
//
//}
//
//glm::vec3* BoundingSphere::GetCenter()
//{
//	return center;
//}
//
//void BoundingSphere::SetCenter(glm::vec3* _center)
//{
//	center = _center;
//}
//
//float BoundingSphere::GetRadius()
//{
//	return radius;
//}
//
//bool BoundingSphere::Intersect(const BoundingSphere & other)
//{
//	float radiusDist = radius + other.radius;
//	glm::vec3 distVec = (*other.center - *center);
//	float centerDist = glm::sqrt((distVec.x * distVec.x) + (distVec.y * distVec.y) + (distVec.z * distVec.z));
//	if (centerDist < radiusDist) {
//		return true;
//		//return IntersectData(true, centerDist - radiusDist);
//	}
//	else {
//		return false;
//		//return IntersectData(false, centerDist - radiusDist);
//	}
//}
