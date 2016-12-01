#pragma once

#include "AbstractRenderer.h"
#include <GL\glew.h>
#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "SOIL.h"
#include "FileReader.h"
#include "Shader.h"
#include "Camera.h"
#include <iostream>
#include <map>
#include "ft2build.h"
#include FT_FREETYPE_H
#include "AbstractCamera.h"
class OpenGLRenderer : public AbstractRenderer
{
private:
	//GLuint program;
	//TODO:: camera should be created in scene for multiple camera options... maybe
	Camera *camera;
	AbstractCamera *cam;
	GLuint VAO, VBO;
	Shader textShader;

	GLuint modelHandle, viewHandle, projHandle;

public:
	OpenGLRenderer();
	~OpenGLRenderer();

	void EnableOpenGL();

	//Prepare to render eachmodel 
	void PrepareToRender();
	void Render();
	void PostRender();

	//Set shader program
	void SetProgram(GLuint _program);

	//Delete all buffers, shader program, and arrays
	void Destroy();

	//Render a model using its transform matrix
	void RenderTransform(glm::mat4 transform);

	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

	void SetActiveCamera(Camera &cam);
	Camera* GetActiveCamera();

	void SetActiveCam( AbstractCamera &_cam) { cam = &_cam; }
	AbstractCamera* GetActiveCam() { return cam; }
};