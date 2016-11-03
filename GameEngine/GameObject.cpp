#include "GameObject.h"


GameObject::GameObject(SimpleModel *_model, BoundingSphere _sphere)
{
	model = _model;
	sphere = _sphere;

	movement = glm::vec3(0.0f, 0.0f, 0.0f); //default to 0,0,0
	rotation = glm::vec3(0.0f, 0.0f, 1.0f);
	angle = 0.0f;
}

GameObject::~GameObject()
{
}

GameObject::GameObject()
{
}

void GameObject::OnInput(Uint32 event, SDL_Keycode key)
{	
	
}

void GameObject::Update(double deltaTime)
{
	transform = glm::translate(transform, glm::vec3(movement.x * deltaTime,
		movement.y * deltaTime,
		movement.z * deltaTime));
	transform = glm::rotate(transform, (float)deltaTime * angle, rotation);
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
glm::vec3 GameObject::GetMovement()
{
	return movement;
}

void GameObject::SetMovement(glm::vec3 _movement)
{
	movement = _movement;
}

glm::vec3 GameObject::GetRotation()
{
	return rotation;
}

void GameObject::SetRotation(glm::vec3 _rotation)
{
	rotation = _rotation;
}

float GameObject::GetAngle()
{
	return angle;
}

void GameObject::SetAngle(float _angle)
{
	angle = _angle;
}

