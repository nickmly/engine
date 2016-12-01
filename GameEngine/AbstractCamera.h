#pragma once
#include "Plane.h"
#include <gtc/matrix_transform.hpp>
class AbstractCamera
{
public:
	AbstractCamera(void);
	~AbstractCamera(void);

	//Setup Projection Settings
	void SetupProjection(const float fovy, const float aspectRatio, const float near = 0.1f, const float far = 1000.0f);

	virtual void  Update() = 0;
	virtual void Rotate(const float yaw, const float pitch, const float roll);

	//Frustum Variables
	void CalcFrustumPlanes();
	bool IsPointInFrustum(const glm::vec3& point);
	bool IsSphereInFrustum(const glm::vec3& center, const float radius);
	bool IsBoxInFrustum(const glm::vec3& min, const glm::vec3& max);

	void GetFrustumPlanes(glm::vec4 _planes[6]); //Apply frustum planes to this camera planes 

	glm::vec3 farPts[4];
	glm::vec3 nearPts[4];

protected:
	//camera settings
	float yaw, pitch, roll, fov, aspect_ratio, Znear, Zfar; 
	
	static glm::vec3 UP;//defines a static UP used accross all cameras
	
	//variables for view Matrix
	glm::vec3 look; //direction in which we want to look
	glm::vec3 up; // camera up orientation 
	glm::vec3 right; // horizontal axis, the crossProduct of look and up

	glm::vec3 position;	//Camera World position

	glm::mat4 ViewMatrix; //viewMatrix
	glm::mat4 ProjMatrix; //ProjectionMatrix

	Plane planes[6]; //frustum planes for clipping calculations

public: //ACCESSORS MUTATORS

	const glm::mat4 GetViewMatrix() const; // returns ViewMatrix for rendering
	const glm::mat4 GetProjMatrix() const; // returns ProjMatrix for rendering

	//camera position
	void SetPosition(const glm::vec3& p);
	const glm::vec3 GetPosition() const;

	//camera Field of View
	void SetFOV(const float fov);
	const float GetFOV() const;

	const float GetAspectRatio() const;

public:
	virtual void Walk(float dist) = 0;
	virtual void Strafe(float dist) = 0;
	virtual void Lift(float dist) = 0;
};

