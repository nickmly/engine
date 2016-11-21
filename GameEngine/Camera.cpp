
#include "Camera.h"
#include "Frustum.h"

Camera::Camera()
{
}

Camera::Camera(CameraType _type, float _width, float _height)
{
	type = _type;
	width = _width;
	height = _height;
	frustum = new Frustum();
}

void Camera::SetProgram(GLuint _program)
{
	program = _program;
	modelHandle = glGetUniformLocation(program, "model"); // Assign modelHandle to uniform value model in shader program
	viewHandle = glGetUniformLocation(program, "view");
	projHandle = glGetUniformLocation(program, "projection");
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
	glUniformMatrix4fv(viewHandle, 1, GL_FALSE, &view[0][0]); // Send it to the GLSL file
	glUniformMatrix4fv(projHandle, 1, GL_FALSE, &projection[0][0]); // Send it to the GLSL file
	glUniformMatrix4fv(modelHandle, 1, GL_FALSE, &_model[0][0]); // Send it to the GLSL file
}

void Camera::Render() {
	view = glm::lookAt(positionVector, targetVector, upVector);
	if(type == CameraType::PROJECTION)
		projection = glm::perspective(glm::radians(60.0f), 800.0f/600.0f, 0.1f, 100.0f);
	else if (type == CameraType::ORTHO)
		projection = glm::ortho(0.0f, width, 0.0f, height,  nearClipPlane, farClipPlane);
}

void Camera::ResizeFrustum(float _ratio, float _near, float _far)
{
	frustum->windowResized(fov, _ratio, _near, _far);
	frustum->cameraChanged(positionVector, targetVector, upVector);
}

bool Camera::IsInsideFrustum(glm::vec3 & cent, float radius)
{
	return frustum->isInside(cent, radius) == Frustum::INSIDE;
}


Camera::~Camera()
{
}
