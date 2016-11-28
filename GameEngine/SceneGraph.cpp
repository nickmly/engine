#include "SceneGraph.h"



SceneGraph::SceneGraph()
{
	rootSceneNode = new SceneNode();
}

SceneGraph::~SceneGraph()
{
}

void SceneGraph::AppendSceneNode(SceneNode *node)
{
	rootSceneNode->AppendChild(node);
}

void SceneGraph::RemoveSceneNode(SceneNode *node)
{
}

void SceneGraph::RenderSceneGraph()
{
	rootSceneNode->RenderSceneNode();
}

