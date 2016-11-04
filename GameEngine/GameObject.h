#pragma once
#include "SDL.h"
#include "BoundingSphere.h"
#include "SimpleModel.h"

class GameObject
{
private:
	SimpleModel *model;
	BoundingSphere sphere;	
	glm::mat4 transform;
	glm::vec3 velocity;
	glm::vec3 rotation;
	glm::vec3* position;
	glm::vec3 initialVelocity;
	glm::vec3 accel;
	glm::vec3 newPos;
	glm::vec3 force;
	float mass;
	float angle;
	OpenGLRenderer* renderer;
public:

	GameObject();
	void OnInput(Uint32 event, SDL_Keycode key);
	void Update(double deltaTime);
	void Render();
	glm::mat4 GetTransform();
	glm::vec3 GetVelocity();
	void SetVelocity(glm::vec3 _velocity);
	glm::vec3 GetAcceleration();
	void SetAcceleration(glm::vec3 _accel);
	glm::vec3 GetRotation();
	void SetRotation(glm::vec3 _rotation);
	glm::vec3* GetPosition();
	void SetPosition(glm::vec3 &_position);
	void UpdatePosition();
	void UpdateRotation();
	void clearForces();
	void clearForces_X();
	void clearForces_Y();
	void clearForces_Z();
	float GetAngle();

	void AddForce(glm::vec3 _forceVec);
	void SetAngle(float _angle);
	BoundingSphere GetSphere();
	GameObject(SimpleModel *_model, BoundingSphere _sphere, OpenGLRenderer &_rend);
	~GameObject();
};

