#include "SceneNode.h"

SceneNode::SceneNode()
{
	firstChild = lastChild = prevSibling = nextSibling = parent = NULL;
}

SceneNode::~SceneNode()
{
}

void SceneNode::AppendChild(SceneNode  *_newBorn)
{
	_newBorn->parent = this;
	_newBorn->SetTransform(transform);
	if (lastChild == NULL) {
		firstChild = _newBorn;
	}
	else{
		lastChild->nextSibling = _newBorn;
		_newBorn->prevSibling = lastChild;
	}
	//set last child to the newBorn 
	lastChild = _newBorn;
}

void SceneNode::RemoveChild(SceneNode *node) {
	SceneNode *current;
	for (current = firstChild; current != NULL; current = current->nextSibling);
	{
		if (current == node)
		{
			if (node->prevSibling) {
				node->prevSibling->nextSibling = node->nextSibling;
			}
			else {
				firstChild = node->nextSibling;
			}
			if (node->nextSibling) {
				node->nextSibling->prevSibling = node->prevSibling;
			}
			else {
				lastChild = node->prevSibling;
			}
			node->parent = NULL;
			return;
		}
	}
}

void SceneNode::ReParent(SceneNode *_adoptiveParent)
{
	parent = _adoptiveParent;
}

void SceneNode::AttachMesh(Model *model)
{	
	model->SetTransform(transform);
	MeshList.push_back(model);
}

void SceneNode::RenderSceneNode()
{
	if (MeshList.size() != 0) {
		for (int i = 0; i < MeshList.size(); i++)
		{
			MeshList.at(i)->SetTransform(transform);
			MeshList.at(i)->Render();
		}
	}
	SceneNode *child = firstChild;
	while (child != NULL) {
		child->RenderSceneNode();
		child = child->nextSibling;
	}
}

glm::vec3 SceneNode::GetWorldLocation()
{
	glm::vec3 result;
	if (parent != nullptr) {
		result = parent->GetWorldLocation();
	}
	/*result = result + location;*/
	return result;
}

void SceneNode::TranslateTransform(const glm::vec3 & _stepPosition)
{
	translationMat = glm::translate(translationMat, _stepPosition);
	UpdateTransformMat();
}

void SceneNode::RotateTransform(const glm::vec3 & _rotation)
{	
	rotationMat = glm::rotate(rotationMat, _rotation.x , glm::vec3(1.0f, 0.0f, 0.0f));
	rotationMat = glm::rotate(rotationMat, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMat = glm::rotate(rotationMat, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	UpdateTransformMat();
}

void SceneNode::ScaleTransform(const glm::vec3 & scale)
{
	scalingMat = glm::scale(scalingMat, scale);
	UpdateTransformMat();
}

void SceneNode::UpdateTransformMat()
{
	transform = translationMat * rotationMat * scalingMat;

	if (parent)
	{
		transform = parent->GetTransform() * transform;
	}

	SceneNode *child = firstChild;
	while (child != NULL) {
		child->UpdateTransformMat();
		child = child->nextSibling;
	}
}

SceneNode::mesh_iterator SceneNode::MeshBegin()
{
	return MeshList.begin();
}
SceneNode::mesh_iterator SceneNode::MeshEnd()
{
	return MeshList.end();
}