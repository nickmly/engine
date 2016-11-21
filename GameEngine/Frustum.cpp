#include "Frustum.h"

#define ANG2RAD 3.14159265358979323846/180.0

void Frustum::windowResized(float _angle, float _ratio, float nearD, float farD)
{
	angle = _angle;
	ratio = _ratio;
	nearDist = nearD;
	farDist = farD;

	/////////////////////////////////////////////////////////
	// Compute width & height of near & far planes
	/////////////////////////////////////////////////////////
	tang = (float)tan(ANG2RAD * angle * 0.5);
	nearHt = nearDist * tang;
	nearWd = nearHt * ratio;
	farHt = farDist * tang;
	farWd = farHt * ratio;
}

void Frustum::cameraChanged(glm::vec3 &camPosn, glm::vec3 &lookAt, glm::vec3 &up)
{
	////////////////////////////////////////////////
	// Compute the view direction of the camera
	////////////////////////////////////////////////
	viewDir = glm::normalize(camPosn - lookAt);

	////////////////////////////////////////////////
	// The right vect is the up vector cross the view vector
	////////////////////////////////////////////////
	rightDir = glm::normalize(glm::cross(up, viewDir));

	/////////////////////////////////////////////////////////
	// Re-compute up vect as cross product of viewDie & rightDir
	/////////////////////////////////////////////////////////
	upDir = glm::cross(viewDir, rightDir);

	////////////////////////////////////////////////
	// Compute centres of near and far planes
	////////////////////////////////////////////////
	nearCent = camPosn - (viewDir * nearDist);
	farCent = camPosn - (viewDir * farDist);

	//////////////////////////////////////////////////
	// Compute 4 corners of near plane
	//////////////////////////////////////////////////
	ntl = nearCent + upDir * nearHt - rightDir * nearWd;
	ntr = nearCent + upDir * nearHt + rightDir * nearWd;
	nbl = nearCent - upDir * nearHt - rightDir * nearWd;
	nbr = nearCent - upDir * nearHt + rightDir * nearWd;

	//////////////////////////////////////////////////
	// Compute 4 corners of far plane
	//////////////////////////////////////////////////
	ftl = farCent + upDir * farHt - rightDir * farWd;
	ftr = farCent + upDir * farHt + rightDir * farWd;
	fbl = farCent - upDir * farHt - rightDir * farWd;
	fbr = farCent - upDir * farHt + rightDir * farWd;

	//////////////////////////////////////////////////
	// Compute the 6 planes
	//////////////////////////////////////////////////
	planes[TOPP] = Plane(ntr, ntl, ftl);
	planes[BOTTOMP] = Plane(nbl, nbr, fbr);
	planes[LEFTP] = Plane(ntl, nbl, fbl);
	planes[RIGHTP] = Plane(nbr, ntr, fbr);
	planes[NEARP] = Plane(ntl, ntr, nbr);
	planes[FARP] = Plane(ftr, ftl, fbl);
}

Frustum::EnclosureType Frustum::isInside(glm::vec3 &pt)
{
	for (int i = 0; i < 6; i++)
	{
		if (planes[i].GetSignedDistance(pt) < 0)
		{
			return OUTSIDE;
		}
	}
	return INSIDE;
}

Frustum::EnclosureType Frustum::isInside(glm::vec3 &cent, float radius)
{
	float distance;
	EnclosureType result = INSIDE;

	for (int i = 0; i < 6; i++)
	{
		distance = planes[i].GetSignedDistance(cent);
		if (distance < -radius) return OUTSIDE;
		else if (distance < radius) result = OVERLAP;
	}
	return result;
}

//Frustum::EnclosureType Frustum::isInside(BoundingBox &box)
//{
//	EnclosureType result = INSIDE;
//
//	for (int i = 0; i < 6; i++)
//	{
//		// test positive vertex to see if it is outside
//		if (planes[i].GetSignedDistance(box.getPositiveVertex(planes[i].GetNormal())) < 0)
//			return OUTSIDE;
//		// is negative vertex outside?
//		else if (planes[i].GetSignedDistance(box.getNegativeVertex(planes[i].GetNormal())) < 0)
//			return OVERLAP;
//	}
//	return result;
//}


Frustum::Frustum()
{
}

