#pragma once
#include "GL/glew.h"
#include <iostream>
class Shader
{
private:
	GLuint program;
public:
	Shader();
	Shader(const char* _vertexFile, const char* _fragFile);
	~Shader();
	void Use();
	GLuint GetProgram();
};

