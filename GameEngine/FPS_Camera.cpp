#include "FPS_Camera.h"



FPS_Camera::FPS_Camera()
{
	translation = glm::vec3(0.0f);
	speed = 0.5f; // 0.5 m/s
}

FPS_Camera::~FPS_Camera()
{
}

void FPS_Camera::Update()
{
	//reference current YPR
	glm::mat4 YPR = glm::yawPitchRoll(yaw, pitch, roll);

	//update position by adding change in translation
	position += translation;

	//apply Yaw Pitch Roll to camera
	look = glm::vec3(YPR * glm::vec4(0, 0, 1, 0));
	up = glm::vec3(YPR * glm::vec4(0, 1, 0, 0));

	//right direction will always be the cross between the up and look directions
	right = glm::cross(look, up);
	
	//target is set from adding the position to where we want to look 
	glm::vec3 target = position + look;

	//Update View Matrix
	ViewMatrix = glm::lookAt(position, target, up);

}

void FPS_Camera::Walk(const float _distance)
{
	//uses look as the direction to translate
	translation += (look*speed*_distance);
	Update();
	translation = glm::vec3(0.0f);
}

void FPS_Camera::Strafe(const float _distance)
{
	//uses right as the direction to translate
	translation += (right*speed*_distance);
	Update();
	translation = glm::vec3(0.0f);
}

void FPS_Camera::Lift(const float _distance)
{
	//uses up as the direction to translate
	translation += (up*speed*_distance);
	Update();
	translation = glm::vec3(0.0f);
}

