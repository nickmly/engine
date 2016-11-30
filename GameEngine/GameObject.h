#pragma once
#include "SDL.h"
#include "BoundingSphere.h"
#include "BoundingBox.h"
#include "Model.h"
#include "SceneNode.h"

class GameObject
{
private:
	//connection to sceneGraph
	//scenenode contains the transform matrix for the world position
	SceneNode   *sceneNode;
	//model passed in for now, this should be a component **MESH**
	Model *model;

	//World transform variables
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

public:

	GameObject();
	GameObject(Model &_model);
	~GameObject();

	void Update(float deltaTime);
	
	//place object in SceneGraph
	void AttachToScene(SceneNode *_sceneNode) { _sceneNode->AppendChild(sceneNode); }

	//*********SETTERS***********//
	void SetPosition(const glm::vec3 &_position) { position = _position; sceneNode->TranslateTransform(position); }
	void SetRotation(const glm::vec3 &_rotation) { rotation = _rotation; sceneNode->RotateTransform(rotation); }
	void SetScale	(const glm::vec3 &_scale)	 { scale = _scale;		 sceneNode->ScaleTransform(scale); }

	//*********GETTERS**********//
	SceneNode* GetSceneNode() { return sceneNode; }

	glm::vec3  GetPosition() { return position; }
	glm::vec3  GetRotation() { return rotation; }
	glm::vec3  GetScale()	 { return scale; }


};

