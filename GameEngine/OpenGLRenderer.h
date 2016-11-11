#pragma once

#include "AbstractRenderer.h"
#include <GL\glew.h>
#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "Camera.h"
#include "SOIL.h"
#include "FileReader.h"
#include "Shader.h"
#include <iostream>
#include <map>
#include "ft2build.h"
#include FT_FREETYPE_H

class OpenGLRenderer : public AbstractRenderer
{
private:
	GLuint program;
	Camera camera;
	GLuint VAO, VBO;
	Shader textShader;
public:
	virtual void RenderPrimitive(PrimitiveType prim);
	void EnableOpenGL();

	//Prepare to render each model
	void PrepareToRender(); 

	//Set shader program
	void SetProgram(GLuint _program);
	
	//Delete all buffers, shader program, and arrays
	void Destroy();

	void RenderSimpleModel();

	//Render a model using its transform matrix
	void RenderTransform(glm::mat4 transform);

	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);		

};