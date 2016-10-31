#pragma once
#include "AbstractRenderer.h"
#include <GL\glew.h>
#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "Camera.h"
#include "SOIL.h"
#include "SDL_image.h"
#include <iostream>

class OpenGLRenderer : public AbstractRenderer
{
private:
	GLuint buffers[3];
	GLuint program;
	Camera camera;
	GLuint VAO;
	//GLuint VBO, VAO, EBO, COLOR, TEXTURE;
	GLuint currentTexture;
	std::vector<glm::vec3> vertices, colors;
	std::vector<glm::vec2> textures;
public:
	virtual void RenderPrimitive(PrimitiveType prim)
	{
		switch (prim) {
		case PrimitiveType::TRIANGLE:
			RenderTriangle();
			break;
		case PrimitiveType::SQUARE:
			// add code here
			break;
		}
	}

	//Draw a triangle to the screen
	void RenderTriangle()
	{
		GLfloat vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f,
		};
		glGenBuffers(1, buffers);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
	}

	void AssignVertices(std::vector<Vertex> _vertices) {
		glm::vec3 newVertex;
		glm::vec2 new2DVertex;
		for (int i = 0; i < _vertices.size(); i++) { // Loop through all the vertices in the vector
			switch (_vertices[i].type)
			{
			case Vertex::POSITION: // If position, take only x,y,z values
				newVertex = glm::vec3(_vertices[i].values.x, _vertices[i].values.y, _vertices[i].values.z);
				vertices.insert(vertices.end(), newVertex);
				break;
			case Vertex::COLOR: // If color, take only x,y,z values
				newVertex = glm::vec3(_vertices[i].values.x, _vertices[i].values.y, _vertices[i].values.z);
				colors.insert(colors.end(), newVertex);
				break;
			case Vertex::NORMAL:
				break;
			case Vertex::TEXTURE:
				new2DVertex = glm::vec2(_vertices[i].values.x, _vertices[i].values.y);
				textures.insert(textures.end(), new2DVertex);
				break;
			}
		}
		glEnable(GL_DEPTH_TEST);
		//GLuint indices[] = {  // Note that we start from 0!
		//	0, 1, 3,  // First Triangle
		//	1, 2, 3   // Second Triangle
		//};

	
		glGenBuffers(3, buffers);
		glGenVertexArrays(1, &VAO);
		//glGenBuffers(1, &EBO);
		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindAttribLocation(program, 0, "vPosition");
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &colors[0], GL_STATIC_DRAW);
		glBindAttribLocation(program, 1, "vertexColor");
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
		glBufferData(GL_ARRAY_BUFFER, textures.size() * sizeof(glm::vec2), &textures[0], GL_STATIC_DRAW);
		glBindAttribLocation(program, 2, "texCoord");
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
		


		glGenTextures(1, &currentTexture);
		glBindTexture(GL_TEXTURE_2D, currentTexture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
													  // Set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		GLint width, height;
		// Load image, create texture and generate mipmaps
		unsigned char* image = SOIL_load_image("wall.jpg", &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		//glGenerateMipmap(GL_TEXTURE_2D);

		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

		camera = Camera(program); // Setup our camera
	}

	void RenderVertices() {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);	
		glClear(GL_DEPTH_BUFFER_BIT);
		//glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0));
		camera.fov = 80;
		camera.SetPositionVector(0.0f, -10.0f, 4.0f); // Put camera at this position
		camera.SetTargetVector(0.0f, 0.0f, 0.0f); // Look at this position
		camera.SetUpVector(0.0f, 1.0f, 0.0f); // Camera is pointing up (0,-1,0) for down
		camera.Render();


		glBindTexture(GL_TEXTURE_2D, currentTexture);

		glUseProgram(program);

		//glUniform1i(glGetUniformLocation(program, "ourTexture"), 0);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		//glDrawElements(GL_TRIANGLES, vertices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		//glDrawArrays(GL_POLYGON, 0, vertices.size());
		
	}

	void UseProgram(GLuint _program) {
		program = _program;
		glLinkProgram(program);
		glUseProgram(program);
	}

	void Destroy() {
		glDeleteBuffers(3, buffers);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDeleteProgram(program);
	}

	void RenderSimpleModel(std::vector<Vertex> vertices) {

	}

	void RenderTransform(glm::mat4 transform) {
		camera.RenderModel(transform);
	}
};