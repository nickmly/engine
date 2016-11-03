#include "GameObject.h"


GameObject::GameObject(SimpleModel *_model, BoundingSphere _sphere, OpenGLRenderer &_rend)
{
	renderer = &_rend;
	model = _model;
	sphere = _sphere;
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	velocity = glm::vec3(0.0f, 0.0f, 0.0f); //default to 0,0,0
	rotation = glm::vec3(0.0f, 0.0f, 1.0f);
	initialVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
	accel = glm::vec3(0.0f, 0.0f, 0.0f);
	angle = 0.0f;
}

GameObject::~GameObject()
{
}

GameObject::GameObject()
{
}

BoundingSphere GameObject::GetSphere()
{
	return sphere;
}

void GameObject::OnInput(Uint32 event, SDL_Keycode key)
{	
	
}

void GameObject::Update(double deltaTime)
{
	velocity = initialVelocity + accel * (float)deltaTime;
	position = initialVelocity * (float)deltaTime + (0.5f*accel) * (float)(deltaTime*deltaTime);
	initialVelocity = velocity;
	
	UpdatePosition();
	transform = glm::rotate(transform, (float)deltaTime * angle, rotation);	
}

void GameObject::UpdatePosition() 
{
	sphere.SetCenter(position);
	transform = glm::translate(transform, glm::vec3(position));
}

void GameObject::UpdateRotation() {

}

void GameObject::Render()
{
	model->RenderModel();
	model->SetTransform(transform);
}


glm::mat4 GameObject::GetTransform()
{
	return transform;
}

glm::vec3 GameObject::GetVelocity()
{
	return velocity;
}

void GameObject::SetVelocity(glm::vec3 _velocity)
{
	velocity = _velocity;
}

glm::vec3 GameObject::GetAcceleration()
{
	return accel;
}

void GameObject::SetAcceleration(glm::vec3 _accel)
{
	accel = _accel;
}

glm::vec3 GameObject::GetRotation()
{
	return rotation;
}

void GameObject::SetRotation(glm::vec3 _rotation)
{
	rotation = _rotation;
}

glm::vec3 GameObject::GetPosition()
{
	return position;
}

void GameObject::SetPosition(glm::vec3 _position)
{
	position = _position;
	UpdatePosition();
}

float GameObject::GetAngle()
{
	return angle;
}

void GameObject::SetAngle(float _angle)
{
	angle = _angle;
}

