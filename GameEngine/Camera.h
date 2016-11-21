#pragma once
#include <GL\glew.h>
#include <vector>
#include "glm.hpp"
#include "gtc\matrix_transform.hpp"

class Frustum;


class Camera
{
private:
	Frustum *frustum;
	GLuint modelHandle, viewHandle, projHandle;
	glm::vec3 positionVector, targetVector, upVector;
	glm::mat4 view, projection;
	GLuint program;
	
public:
	enum CameraType {
		PROJECTION,
		ORTHO
	};
	CameraType type;
	float fov = 60.0f;
	float width, height;
	float nearClipPlane = 0.1f;
	float farClipPlane = 100.0f;
	Camera();
	Camera(CameraType _type, float _width, float _height);
	void SetProgram(GLuint _program);
	void SetPositionVector(float _x, float _y, float _z);
	void SetTargetVector(float _x, float _y, float _z);
	void SetUpVector(float _x, float _y, float _z);
	void RenderModel(glm::mat4 _model);
	void Render();
	void ResizeFrustum(float _ratio, float _near, float _far);
	bool IsInsideFrustum(glm::vec3 &cent, float radius);
	~Camera();
};

