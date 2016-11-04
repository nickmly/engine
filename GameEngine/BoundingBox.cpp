#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
}


BoundingBox::~BoundingBox()
{
}

BoundingBox::BoundingBox(glm::vec3 &_center,glm::vec3 &_scale) { 
	center = &_center;
	scale = _scale;
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

void BoundingBox::SetCenter(glm::vec3 *_center) {
	center = _center;
	Xmin = center->x - (scale.x*0.5f);
	Xmax = center->x + (scale.x*0.5f);
	Ymin = center->y - (scale.y*0.5f);
	Ymax = center->y + (scale.y*0.5f);
	Zmin = center->z - (scale.z*0.5f);
	Zmax = center->z + (scale.z*0.5f);
}
void BoundingBox::SetScale(glm::vec3 &_scale) {
	scale = _scale;
}




