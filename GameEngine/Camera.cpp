
#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(GLuint _program)
{
	modelHandle = glGetUniformLocation(_program, "model"); // Assign modelHandle to uniform value model in shader program
	viewHandle = glGetUniformLocation(_program, "view"); 
	projHandle = glGetUniformLocation(_program, "projection"); // Assign modelHandle to uniform value model in shader program
}

void Camera::SetPositionVector(float _x, float _y, float _z)
{
	positionVector = glm::vec3(_x, _y, _z);
}

void Camera::SetTargetVector(float _x, float _y, float _z)
{
	targetVector = glm::vec3(_x, _y, _z);
}

void Camera::SetUpVector(float _x, float _y, float _z)
{
	upVector = glm::vec3(_x, _y, _z);
}

void Camera::RenderModel(glm::mat4 _model) 
{
	glUniformMatrix4fv(modelHandle, 1, GL_FALSE, &_model[0][0]); // Send it to the GLSL file
}

void Camera::Render() {
	view = glm::lookAt(positionVector, targetVector, upVector);
	projection = glm::perspective(glm::radians(fov), aspectRatio, nearClipPlane, farClipPlane);	
	glUniformMatrix4fv(viewHandle, 1, GL_FALSE, &view[0][0]); // Send it to the GLSL file
	glUniformMatrix4fv(projHandle, 1, GL_FALSE, &projection[0][0]); // Send it to the GLSL file
}

Camera::~Camera()
{
}
