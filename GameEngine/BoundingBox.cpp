#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
}


BoundingBox::~BoundingBox()
{
}

BoundingBox::BoundingBox(glm::vec3 &_center) { 
	center = &_center;
}

bool BoundingBox::BoxIntersects(const BoundingBox & otherBox) {
	if (Xmax > otherBox.Xmin &&
		Xmin < otherBox.Xmax &&
		Ymax > otherBox.Ymin &&
		Ymin < otherBox.Ymax &&
		Zmax > otherBox.Zmin &&
		Zmin < otherBox.Zmax) {
		return true;
	}
	else {
		return false;
	}
}

void BoundingBox::SetCenter(glm::vec3 &_center) {
	center = &_center;
	Xmin = center->x - (scale.x);
	Xmax = center->x + (scale.x);
	Ymin = center->y - (scale.y);
	Ymax = center->y + (scale.y);
	Zmin = center->z - (scale.z);
	Zmax = center->z + (scale.z);
}							    
void BoundingBox::SetScale(glm::vec3 &_scale) {
	scale = _scale;
}




