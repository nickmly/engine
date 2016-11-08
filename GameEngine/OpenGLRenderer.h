#pragma once

#include "AbstractRenderer.h"
#include <GL\glew.h>
#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "Camera.h"
#include "SOIL.h"
#include "FileReader.h"
#include "ShaderLoader.h"
#include <iostream>
#include <map>
#include "ft2build.h"
#include FT_FREETYPE_H

class OpenGLRenderer : public AbstractRenderer
{
private:
	GLuint buffers[4];
	GLuint program, textProgram;
	Camera camera;
	GLuint VAO;
	std::vector<glm::vec3> vertices, colors;
	std::vector<glm::vec2> textures;
	
public:
	virtual void RenderPrimitive(PrimitiveType prim);
	//Draw a triangle to the screen
	void RenderTriangle();	
	//Generate buffers and load all vertex positions, colors, and texture coordinates into the vertex array
	void AssignVertices(std::vector<Vertex> _vertices);
	void EnableOpenGL();
	
	std::vector<glm::vec3> &getGlobalVertices();
	std::vector<glm::vec3> &getGlobalColors();
	std::vector<glm::vec2> &getGlobalTextures();

	// Render all vertices
	void RenderVertices();

	//Prepare to render each model
	void PrepareToRender(); 
	
	//Link a shader program for first time use. Must call glUseProgram after first time!
	void UseProgram(GLuint _program);
	
	//Delete all buffers, shader program, and arrays
	void Destroy();

	void RenderSimpleModel();

	//Render a model using its transform matrix
	void RenderTransform(glm::mat4 transform);

	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);		

};