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

BoundingSphere GameObject::GetSphere(){
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
	
	transform = glm::translate(transform, glm::vec3(position));/* glm::vec3(movement.x * deltaTime,
		movement.y * deltaTime,
		movement.z * deltaTime));*/
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
	return velocity;
}

void GameObject::SetMovement(glm::vec3 _movement)
{
	accel = _movement;
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

