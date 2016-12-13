#pragma once
#include <vector>
#include <string>
#include "GL\glew.h"
#include "Mesh.h"
#include "SOIL.h"
#include "Shader.h"
#include "OpenGLRenderer.h"

//ASSIMP
#include "Importer.hpp"
#include "scene.h"
#include "postprocess.h"


using namespace std;

class Model
{
private:
	Shader shader;
	OpenGLRenderer* renderer;
	glm::mat4 transform;

	vector<Texture> textures_loaded;

	vector<Mesh> meshes;

	string directory;

	void LoadModel(string path);

	void ProcessNode(aiNode* node, const aiScene* scene);

	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

	GLint TextureFromFile(const char* path, string directory);
public:
	Model(GLchar *path, Shader _shader, OpenGLRenderer &_rend);
	Model();
	~Model();
	void Render();

	glm::mat4 GetTransform();
	void SetTransform(glm::mat4 _transform);
};

