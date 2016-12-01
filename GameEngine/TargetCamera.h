#pragma once
#include "AbstractCamera.h"
class TargetCamera :
	public AbstractCamera
{
public:
	TargetCamera(void);
	~TargetCamera(void);

	// Inherited via AbstractCamera
	virtual void Update() override;
	void Rotate(const float yaw, const float pitch, const float roll);
	
	void SetTarget(const glm::vec3 _target);
	const glm::vec3 GetTarget() const { return target; }

	void Pan(const float distanceX, const float distanceY);
	void Zoom(const float amount);
	void Move(const float distanceX, const float distanceZ);

protected:

	glm::vec3 target; //view target

	float minRy, maxRy; //min max rotation on Y
	float distance;
	float minDistance, maxDistance;
};

