#pragma once
#include <vector>
#include <string>
#include "GL\glew.h"
#include "Mesh.h"

//ASSIMP
#include "Importer.hpp"
#include "scene.h"
#include "postprocess.h"

using namespace std;

class Model
{
private:
	vector<Mesh> meshes;
	string directory;

	void LoadModel(GLchar *path);
	
	void ProcessNode(aiNode* node, const aiScene* scene);

public:
	Model(GLchar *path);
	~Model();
	void Render();
};

