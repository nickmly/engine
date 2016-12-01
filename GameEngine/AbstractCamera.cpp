#include "AbstractCamera.h"

glm::vec3 AbstractCamera::UP = glm::vec3(0, 1, 0);

AbstractCamera::AbstractCamera(void)
{
	Znear = 0.1f;
	Zfar = 1000;
}

AbstractCamera::~AbstractCamera(void)
{
}

void AbstractCamera::SetupProjection(const float fovy, const float aspectRatio, const float near, const float far)
{
	ProjMatrix = glm::perspective(fovy, aspectRatio, near, far);
	Znear = near;
	Zfar = far;
	fov = fovy;
	aspect_ratio = aspectRatio;
}

void AbstractCamera::Rotate(const float y, const float p, const float r)
{
	yaw = glm::radians(y);
	pitch = glm::radians(p);
	roll = glm::radians(r);
	Update();
}

const glm::mat4 AbstractCamera::GetViewMatrix() const
{
	return ViewMatrix;
}

const glm::mat4 AbstractCamera::GetProjMatrix() const
{
	return ProjMatrix;
}

void AbstractCamera::SetPosition(const glm::vec3 &p)
{
	position = p;
}

const glm::vec3 AbstractCamera::GetPosition() const
{
	return position;
}

void AbstractCamera::SetFOV(const float _fov)
{
	fov = _fov;
	ProjMatrix = glm::perspective(_fov, aspect_ratio, Znear, Zfar);
}

const float AbstractCamera::GetFOV() const
{
	return fov;
}

const float AbstractCamera::GetAspectRatio() const
{
	return aspect_ratio;
}

void AbstractCamera::CalcFrustumPlanes()
{
	glm::vec3 cN = position + look*Znear;
	glm::vec3 cF = position + look*Zfar;

	float Hnear = 2.0f * tan(glm::radians(fov / 2.0f)) * Znear;
	float Wnear = Hnear * aspect_ratio;
	float Hfar = 2.0f * tan(glm::radians(fov / 2.0f)) * Zfar;
	float Wfar = Hfar * aspect_ratio;
	float hHnear = Hnear / 2.0f;
	float hWnear = Wnear / 2.0f;
	float hHfar = Hfar / 2.0f;
	float hWfar = Wfar / 2.0f;


	farPts[0] = cF + up*hHfar - right*hWfar;
	farPts[1] = cF - up*hHfar - right*hWfar;
	farPts[2] = cF - up*hHfar + right*hWfar;
	farPts[3] = cF + up*hHfar + right*hWfar;

	nearPts[0] = cN + up*hHnear - right*hWnear;
	nearPts[1] = cN - up*hHnear - right*hWnear;
	nearPts[2] = cN - up*hHnear + right*hWnear;
	nearPts[3] = cN + up*hHnear + right*hWnear;

	planes[0] = Plane(nearPts[3], nearPts[0], farPts[0]);
	planes[1] = Plane(nearPts[1], nearPts[2], farPts[2]);
	planes[2] = Plane(nearPts[0], nearPts[1], farPts[1]);
	planes[3] = Plane(nearPts[2], nearPts[3], farPts[2]);
	planes[4] = Plane(nearPts[0], nearPts[3], nearPts[2]);
	planes[5] = Plane(farPts[3], farPts[0], farPts[1]);
}

bool AbstractCamera::IsPointInFrustum(const glm::vec3& point)
{
	for (int i = 0; i < 6; i++)
	{
		if (planes[i].GetSignedDistance(point) < 0)
			return false;
	}
	return true;
}

bool AbstractCamera::IsSphereInFrustum(const glm::vec3& center, const float radius)
{
	for (int i = 0; i < 6; i++)
	{
		float d = planes[i].GetSignedDistance(center);
		if (d < -radius)
			return false;
	}
	return true;
}

bool AbstractCamera::IsBoxInFrustum(const glm::vec3 & min, const glm::vec3 & max)
{
	for (int i = 0; i < 6; i++)
	{
		glm::vec3 p = min, n = max;
		glm::vec3 N = planes[i].GetNormal();
		if (N.x >= 0) {
			p.x = max.x;
			n.x = min.x;
		}
		if (N.y >= 0) {
			p.y = max.y;
			n.y = min.y;
		}
		if (N.z >= 0) {
			p.z = max.z;
			n.z = min.z;
		}

		if (planes[i].GetSignedDistance(p) < 0) {
			return false;
		}
	}
	return true;
}
void AbstractCamera::GetFrustumPlanes(glm::vec4 _planes[6])
{
	for (int i = 0;i < 6;i++) {
		_planes[i] = glm::vec4(planes[i].GetNormal(), planes[i].GetDistance());
	}
}
