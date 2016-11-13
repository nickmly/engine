#include "SimpleModel.h"

SimpleModel::SimpleModel(vector<Vertex> _vert, OpenGLRenderer &_rend, const char* _textureFile,
	char* _vertShader, char* _fragShader)
{
	renderer = &_rend;
	AssignVertices(_vert);

	//Load shaders
	shader = Shader(FileReader::ReadFromFile(_vertShader), FileReader::ReadFromFile(_fragShader));

	// Generate 3 buffers and store them into an array
	glGenBuffers(3, buffers);
	// Generate a vertex array
	glGenVertexArrays(1, &VAO);

	// Bind the Vertex Array Object first, then bind and set vertex buff`er(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	// Bind vertex positions
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, vertPos.size() * sizeof(glm::vec3), &vertPos[0], GL_STATIC_DRAW);
	glBindAttribLocation(shader.GetProgram(), 0, "vPosition");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	// Bind colors
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, vertColor.size() * sizeof(glm::vec3), &vertColor[0], GL_STATIC_DRAW);
	glBindAttribLocation(shader.GetProgram(), 1, "vertexColor");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	//Bind UV coordinates
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, vertUV.size() * sizeof(glm::vec2), &vertUV[0], GL_STATIC_DRAW);
	glBindAttribLocation(shader.GetProgram(), 2, "vtexCoord");
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this 
	
	if (_textureFile) {
		GLint width, height;// Load image, create texture and generate mipmaps
		GLubyte* image = SOIL_load_image(_textureFile, &width, &height, 0, SOIL_LOAD_RGB);
		if (image == 0) {
			printf("Image failed to load");
		}

		// Generate a texture
		glGenTextures(1, &currentTexture);
		glBindTexture(GL_TEXTURE_2D, currentTexture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}	
	scale = glm::vec3(1.0f);
}

SimpleModel::SimpleModel()
{
}


SimpleModel::~SimpleModel()
{
}

void SimpleModel::AssignVertices(std::vector<Vertex> _vertices)
{
	glm::vec3 newVertex;
	glm::vec2 new2DVertex;
	for (int i = 0; i < (int)_vertices.size(); i++) { // Loop through all the vertices in the vector
		switch (_vertices[i].type)
		{
		case Vertex::POSITION: // If position, take only x,y,z values
			newVertex = glm::vec3(_vertices[i].values.x, _vertices[i].values.y, _vertices[i].values.z);
			vertPos.push_back(newVertex);
			break;
		case Vertex::COLOR: // If color, take only x,y,z values
			newVertex = glm::vec3(_vertices[i].values.x, _vertices[i].values.y, _vertices[i].values.z);
			vertColor.push_back(newVertex);
			break;
		case Vertex::NORMAL:
			break;
		case Vertex::TEXTURE:// If texture, take only x,y(UV) values
			new2DVertex = glm::vec2(_vertices[i].values.x, _vertices[i].values.y);
			vertUV.push_back(new2DVertex);
			break;
		}
	}
	
	printf("AssignVertices() called\nNew size of verts: %d\n", vertPos.size());
}

void SimpleModel::RenderModel()
{
	shader.Use();
	renderer->SetProgram(shader.GetProgram());
	if (currentTexture)
		glBindTexture(GL_TEXTURE_2D, currentTexture);
	renderer->RenderTransform(transform);

	//TODO: move this to another class
	GLint lightColorLoc = glGetUniformLocation(shader.GetProgram(), "lightColor");
	glUniform3f(lightColorLoc, 1.0f, 0.8f, 0.5f); // Also set light's color (white)

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertPos.size());
	glBindVertexArray(0);
}

void SimpleModel::AddComponent(Vertex::VertexType type)
{
	switch (type) {
	case Vertex::COLOR:
		colors = true;
		break;
	case Vertex::TEXTURE:
		textures = true;
		break;
	case Vertex::NORMAL:
		normals = true;
		break;
	}
}

void SimpleModel::AddVertices(vector<Vertex> _vert)
{
	//vertices = _vert;
}

void SimpleModel::SetTransform(glm::mat4 _transform)
{
	transform = _transform;
}

void SimpleModel::SetScale(glm::vec3 _scale)
{
	scale = _scale;
}

glm::vec3 SimpleModel::GetScale()
{
	return scale;
}

