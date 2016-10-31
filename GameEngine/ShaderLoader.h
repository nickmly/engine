#pragma once
#include "GL\glew.h"

class ShaderLoader
{
private:
	GLuint program = 0;
public:
	void LoadShader(GLenum shaderType, GLchar* src);
	GLuint GetProgram();
};

