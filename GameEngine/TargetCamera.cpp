#include "TargetCamera.h"
#include <iostream>
#include <gtx/euler_angles.hpp>

TargetCamera::TargetCamera(void)
{
	right = glm::vec3(1, 0, 0);
	up = glm::vec3(0, 1, 0);
	look = glm::vec3(0, 0, -1);
	
	minRy = -60; //Y rotation minimum
	maxRy = 60; // Y rotation maximum
	
	minDistance = 1;
	maxDistance = 10;
}

TargetCamera::~TargetCamera()
{
}

void TargetCamera::Update()
{
	glm::mat4 camYPR = glm::yawPitchRoll(yaw, pitch, 0.0f);
	glm::vec3 zTranslation = glm::vec3(0, 0, distance);

	zTranslation = glm::vec3(camYPR * glm::vec4(zTranslation, 0.0f));

	position = target + zTranslation;

	look = glm::normalize(target - position); //sets look vec to the normalized direction vec between cam position and target
	up = glm::vec3(camYPR * glm::vec4(UP, 0.0f)); // Applies camera rotation to up vector using STATIC UP
	right = glm::cross(look, up); //horizontal axis will be cross between look and up

	//update ViewMatrix
	ViewMatrix = glm::lookAt(position, target, up);

}

void TargetCamera::Rotate(const float yaw, const float pitch, const float roll)
{
	float _pitch = std::fmin(std::fmax(pitch, minRy), maxRy); // rotates about the Y or UP axis
	
	// sends new pitch to base Rotate function
	AbstractCamera::Rotate(yaw, _pitch, roll);

}

void TargetCamera::SetTarget(const glm::vec3 _target)
{
	target = _target; // set new target
	distance = glm::distance(position, target); // update distance
	distance = std::fmax(minDistance, std::fmin(distance, maxDistance)); //restric distance
}

void TargetCamera::Pan(const float distanceX, const float distanceY)
{
	glm::vec3 X = right * distanceX; // expands or contracts horizontal plane
	glm::vec3 Y = up * distanceY; // expands or contracts vertical plane
	position += X + Y; //apply to position
	target += X + Y; //apply to target

	Update(); // update view matrix
}

void TargetCamera::Zoom(const float amount)
{
	position += look * amount; //moves camera in the look direction mulitplied by set amount
	distance = glm::distance(position, target); //calculates distance
	distance = std::fmax(minDistance, std::fmin(distance, maxDistance)); //restricts distance
	
	Update(); // update view matrix
}

void TargetCamera::Move(const float distanceX, const float distanceZ)
{
	glm::vec3 X = right * distanceX; // move along horizontal
	glm::vec3 Y = look * distanceZ; // move along vertical
	position += X + Y; 
	target += X + Y;
	Update(); // update view matrix
}
