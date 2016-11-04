#include "GameObject.h"


GameObject::GameObject(SimpleModel *_model, BoundingSphere _sphere, OpenGLRenderer &_rend)
{
	renderer = &_rend;
	model = _model;
	sphere = _sphere;
	position = new glm::vec3(0.0f, 0.0f, 0.0f);
	velocity = glm::vec3(0.0f, 0.0f, 0.0f); //default to 0,0,0
	rotation = glm::vec3(0.0f, 0.0f, 1.0f);
	initialVelocity =  glm::vec3(0.0f, 0.0f, 0.0f);
	accel = glm::vec3(0.0f,0.0f,0.0f);
	newPos = glm::vec3(0.0f, 0.0f, 0.0f);
	force = glm::vec3(0.0f, 0.0f, 0.0f);
	angle = 0.0f;
	mass = 1.0f;
	

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
	//sets up 
	accel = mass*force;
	velocity = initialVelocity + accel*(float)deltaTime;
	newPos = velocity*(float)deltaTime + (0.5f*accel)*(float)(deltaTime*deltaTime);
	initialVelocity = velocity;
	//dampen acceleration 
	initialVelocity *= 0.9992f;
	
	UpdatePosition();
	transform = glm::rotate(transform, (float)deltaTime * angle, rotation);
}

void GameObject::UpdatePosition()
{
	//translate object to newPos
	transform = glm::translate(transform, glm::vec3(newPos));
	//add previous position to change in position for current positionl
	position = new glm::vec3(newPos + *position);
	sphere.SetCenter(position);
}

void GameObject::UpdateRotation() {

}

void GameObject::clearForces() {
	force = glm::vec3(0.0f, 0.0f, 0.0f); 
}

void GameObject::clearForces_X(){
	force *= glm::vec3(0.0f, 1.0f, 1.0f);
}
void GameObject::clearForces_Y() {
	force *= glm::vec3(1.0f, 0.0f, 1.0f);
}
void GameObject::clearForces_Z() {
	force *= glm::vec3(1.0f, 1.0f, 0.0f);
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
void GameObject::AddForce(glm::vec3 _forceVec) {
	force = _forceVec;
	accel += force;
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

glm::vec3* GameObject::GetPosition()
{
	return position;
}

void GameObject::SetPosition(glm::vec3 &_position)
{
	newPos = _position;
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

