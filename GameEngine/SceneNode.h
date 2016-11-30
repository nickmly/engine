#pragma once

#include <vector>
#include "glm.hpp"
#include "gtc/quaternion.hpp"

#include "Model.h"

class SceneNode
{
public:
	SceneNode();
	~SceneNode();

private:
	//node transform
	glm::mat4 translationMat;
	glm::mat4 scalingMat;
	glm::mat4 rotationMat;
	glm::mat4 transform;

	//root family
	SceneNode *firstChild;
	SceneNode *lastChild;
	SceneNode *prevSibling;
	SceneNode *nextSibling;
	SceneNode *parent;

	//Renderables
	std::vector<Model*> MeshList;

public:

	typedef vector<Model*>::iterator mesh_iterator;
	mesh_iterator MeshBegin();
	mesh_iterator MeshEnd();

	////******Class Functions**********////
	void AppendChild(SceneNode *_newBorn);
	void RemoveChild(SceneNode *node);
	void ReParent(SceneNode *_adoptiveParent);

	void AttachMesh(Model *model);

	void RenderSceneNode();
	////**********ACCESSORS***********////
	glm::vec3 GetWorldLocation();

	SceneNode* GetFirstChild()		{ return firstChild; }
	SceneNode* GetLastChild()		{ return lastChild; }
	SceneNode* GetPrevSibling()		{ return prevSibling; }
	SceneNode* GetNextSibling()		{ return nextSibling; }
	SceneNode* GetParent()			{ return parent; }
	
	//glm::quat GetRotation() const	{ return rotation; }
	//glm::vec3 GetScale() const		{ return scale; }
	//glm::vec3 GetLocation() const	{ return location; }
	glm::mat4 GetTransform() const  { return transform; }

	////*******MUTATORS************////
	//void SetRotation(const glm::vec3 &_rotation)	{ rotation = _rotation; }
	//void SetScale(const glm::vec3 &_scaling)		{ scale = _scaling; }
	//void SetLocation(const glm::vec3 &_location)	{ location = _location; }
	void TranslateTransform(const glm::vec3 & _stepPosition);
	void RotateTransform(const glm::vec3 &rotation);
	void ScaleTransform(const glm::vec3 &scale);
	void SetTransform(const glm::mat4 &_transform) { transform = _transform; }
	void UpdateTransformMat();

};

