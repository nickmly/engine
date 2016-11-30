#include "GameObject.h"

GameObject::GameObject(Model &_model)
{
	model = &_model;
	sceneNode = new SceneNode();
	position = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);

	if (model != NULL) {
		sceneNode->AttachMesh(model);
	}
}
GameObject::~GameObject()
{

}

GameObject::GameObject()
{
}

void GameObject::Update(float deltaTime)
{

}
