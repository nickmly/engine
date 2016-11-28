#pragma once
#include <vector>
#include "SceneNode.h"

class SceneGraph
{
public:
	SceneGraph();
	~SceneGraph();

private:
	SceneNode* rootSceneNode;

public:

	void AppendSceneNode(SceneNode *node);
	void RemoveSceneNode(SceneNode *node);

	void RenderSceneGraph();
	SceneNode* GetRootSceneNode() { return rootSceneNode; }
};

