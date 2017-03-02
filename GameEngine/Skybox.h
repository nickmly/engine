#pragma once
#include "OpenGLRenderer.h"
class Skybox
{
public:
	OpenGLRenderer renderer;
	Skybox(OpenGLRenderer _renderer, std::vector<char*> images);
	void Render();
	~Skybox();
};

