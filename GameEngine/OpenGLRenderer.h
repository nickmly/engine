#pragma once
#include "AbstractRenderer.h"
#include <GL\glew.h>
#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "Camera.h"
#include "SOIL.h"
#include "GLShader.h"

#include <iostream>

class OpenGLRenderer : public AbstractRenderer
{
private:
	GLuint texCoord;
	GLuint texID;
	GLuint buffers[3];
	GLuint program;
	Camera camera;
	GLuint VAO;
	//GLuint VBO, VAO, EBO, COLOR, TEXTURE;
	GLuint currentTexture;
	std::vector<glm::vec3> vertices, colors;
	std::vector<glm::vec2> textures;
public:
	virtual void RenderPrimitive(PrimitiveType prim);
	

	//Draw a triangle to the screen
	void RenderTriangle();	

	//Generate buffers and load all vertex positions, colors, and texture coordinates into the vertex array
	void AssignVertices(std::vector<Vertex> _vertices);
	
	void EnableOpenGL();

	static std::vector<glm::vec3> &getGlobalVertices();

	static std::vector<glm::vec3> &getGlobalColors();

	static std::vector<glm::vec2> &getGlobalTextures();

	// Render all vertices
	void RenderVertices();

	//Link a shader program for first time use. Must call glUseProgram after first time!
	void UseProgram(GLuint _program);

	//Delete all buffers, shader program, and arrays
	void Destroy();

	void RenderSimpleModel(std::vector<Vertex> vertices);

	//Render a model using its transform matrix
	void RenderTransform(glm::mat4 transform);
};