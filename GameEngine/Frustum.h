#pragma once
#include "glm.hpp"
#include "Plane.h"
#include "BoundingBox.h"

class Frustum
{
private:
	/** The names of the 6 planes */
	enum PlaneNames {
		NEARP, FARP, TOPP, BOTTOMP, RIGHTP, LEFTP
	};
	/** The camera position at the apex of the frustum */
	glm::vec3									camPos;
	/** A normalized vector looking in the same direction as the camera */
	glm::vec3									viewDir;
	/** Distance from the camera to the near plane */
	float											nearDist;
	/** Distance from the camera to the far plane */
	float											farDist;
	/** The centre of the near plane */
	glm::vec3										nearCent;
	/** The centre of the far plane */
	glm::vec3										farCent;
	/** Width of the near plane */
	float											nearWd;
	/** Height of the near plane */
	float											nearHt;
	/** Width of the far plane */
	float											farWd;
	/** Height of the far plane */
	float											farHt;
	/** A normalized vector pointing up WRT the camera */
	glm::vec3										upDir;
	/** A normalized vector pointing right WRT the camera */
	glm::vec3										rightDir;
	/** The 6 planes delimiting the frustum */
	Plane											planes[6];
	/** The corner points of the near and far planes */
	glm::vec3										ntl, nbl, nbr, ntr, ftl, fbl, fbr, ftr;
	/** The ratio from the graphics system perspective calculations */
	float											ratio;
	/** The angle of the field of view */
	float											angle;
	/** Tangent of half the angle */
	float											tang;
public:
	/** Used to determine if an object is inside the frustum */
	static enum EnclosureType {
		INSIDE, OUTSIDE, OVERLAP
	};
	Frustum();
	
	/**
	* This handles the situation where the window is resized.  It updates the
	* internal variables to reflect the new window size.
	* @param _angle The field of view angle
	* @param _ratio The ratio used in the perspective
	* @param nearD Distance from eye to near plane
	* @param farD Distance from eye to far plane
	*/
	void windowResized(float _angle, float _ratio, float nearD, float farD);

	/**
	* This is called to recompute the frustum every time the position of the
	* camera changes.
	* @param camPosn The position of the camera
	* @param lookAt The point at which the camera is looking
	* @param up The up vector for the camera
	*/
	void cameraChanged(glm::vec3 &camPosn, glm::vec3 &lookAt, glm::vec3 &up);

	/**
	* Determine if a point is inside the frustum.
	* @param pt The point to check to see if inside the frustum
	* @return Whether the point is inside, outside or overlapping the frustum
	*/
	EnclosureType isInside(glm::vec3 &pt);

	/**
	* Determine if a sphere is inside the frustum.
	* @param cent The centre of the sphere
	* @param radius The radius of the sphere
	* @return Whether the sphere is inside, outside or overlapping the frustum
	*/
	EnclosureType isInside(glm::vec3 &cent, float radius);

	///**
	//* Determine if an axis aligned bounding box is inside the frustum.
	//* @param box The axis aligned bounding box to test
	//* Whether the box is inside, outside or overlapping the frustum
	//*/
	//EnclosureType isInside(BoundingBox &box);
};

