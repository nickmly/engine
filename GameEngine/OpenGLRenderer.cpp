#include "OpenGLRenderer.h"

void OpenGLRenderer::RenderPrimitive(PrimitiveType prim)
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

void OpenGLRenderer::RenderTriangle()
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

void OpenGLRenderer::AssignVertices(std::vector<Vertex> _vertices)
{
	glm::vec3 newVertex;
	glm::vec2 new2DVertex;
	for (int i = 0; i < _vertices.size(); i++) { // Loop through all the vertices in the vector
		switch (_vertices[i].type)
		{
		case Vertex::POSITION: // If position, take only x,y,z values
			newVertex = glm::vec3(_vertices[i].values.x, _vertices[i].values.y, _vertices[i].values.z);
			getGlobalVertices().push_back(newVertex);
			break;
		case Vertex::COLOR: // If color, take only x,y,z values
			newVertex = glm::vec3(_vertices[i].values.x, _vertices[i].values.y, _vertices[i].values.z);
			getGlobalColors().push_back(newVertex);
			break;
		case Vertex::NORMAL:
			break;
		case Vertex::TEXTURE:// If texture, take only x,y(UV) values
			new2DVertex = glm::vec2(_vertices[i].values.x, _vertices[i].values.y);
			getGlobalTextures().push_back(new2DVertex);
			break;
		}
	}
	printf("Vert Size before enable opengl: %d\n", getGlobalVertices().size());
}

void OpenGLRenderer::EnableOpenGL()
{
	printf("Vert Size after enable opengl: %d\n", getGlobalVertices().size());
	GLint width, height;									  // Load image, create texture and generate mipmaps
	GLubyte* image = SOIL_load_image("wall.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	if (image == 0) {
		printf("Image failed to load");
	}


	//GLuint program = LoadShader("shader.vert", "shader.frag");
	//glUseProgram(program);

	//Enable depth test to prevent some faces from being invisible
	glEnable(GL_DEPTH_TEST);

	// Generate a texture
	glGenTextures(1, &currentTexture);
	glBindTexture(GL_TEXTURE_2D, currentTexture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	/*
	GLuint program = LoadShader("shader.vert", "shader.frag");
	glUseProgram(program);*/
	texCoord = glGetAttribLocation(program, "vtexCoord");
	glEnableVertexAttribArray(texCoord);
	glVertexAttribPointer(texCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
	texID = glGetAttribLocation(program, "texture");
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(texID, 0);

	//glGenerateMipmap(GL_TEXTURE_2D);

	printf("width %i \n", width);
	printf("height %i \n", height);

	SOIL_free_image_data(image); // Free image from memory
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

									 // Generate 3 buffers and store them into an array
	glGenBuffers(3, buffers);
	// Generate a vertex array
	glGenVertexArrays(1, &VAO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	// Bind vertex positions
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, getGlobalVertices().size() * sizeof(glm::vec3), &getGlobalVertices()[0], GL_STATIC_DRAW);
	glBindAttribLocation(program, 0, "vPosition");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	// Bind colors
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, getGlobalColors().size() * sizeof(glm::vec3), &getGlobalColors()[0], GL_STATIC_DRAW);
	glBindAttribLocation(program, 1, "vertexColor");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	//Bind UV coordinates
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, getGlobalTextures().size() * sizeof(glm::vec2), &getGlobalTextures()[0], GL_STATIC_DRAW);
	glBindAttribLocation(texID, 2, "vtexCoord");
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);

	// Unbind buffers and arrays to clear memory
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

	camera = Camera(Camera::PROJECTION, 800, 600, program); // Setup our camera
}

std::vector<glm::vec3>& OpenGLRenderer::getGlobalVertices()
{
	static std::vector<glm::vec3> g_vertices;
	return g_vertices;
}

std::vector<glm::vec3>& OpenGLRenderer::getGlobalColors()
{
	static std::vector<glm::vec3> g_colors;
	return g_colors;
}

std::vector<glm::vec2>& OpenGLRenderer::getGlobalTextures()
{
	static std::vector<glm::vec2> g_textures;
	return g_textures;
}

void OpenGLRenderer::RenderVertices()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera.fov = 80;
	camera.SetPositionVector(0.0f, -10.0f, 4.0f); // Put camera at this position
	camera.SetTargetVector(0.0f, 0.0f, 0.0f); // Look at this position
	camera.SetUpVector(0.0f, 1.0f, 0.0f); // Camera is pointing up (0,-1,0) for down
	camera.Render();

	glBindTexture(GL_TEXTURE_2D, currentTexture);

	glUseProgram(program);

	//glUniform1i(glGetUniformLocation(program, "myTexture"), 0);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);
}

void OpenGLRenderer::UseProgram(GLuint _program)
{
	program = _program;
	glLinkProgram(program);
	glUseProgram(program);
}

void OpenGLRenderer::Destroy()
{
	glDeleteBuffers(3, buffers);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDeleteProgram(program);
}

void OpenGLRenderer::RenderSimpleModel(std::vector<Vertex> vertices)
{
}

void OpenGLRenderer::RenderTransform(glm::mat4 transform)
{
	camera.RenderModel(transform);
}




