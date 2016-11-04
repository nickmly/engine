#include "SimpleModel.h"

SimpleModel::SimpleModel(vector<Vertex> _vert, OpenGLRenderer &_rend, const char* textureFile)
{
	vertices = _vert;
	renderer = &_rend;
	renderer->AssignVertices(vertices);
	if (textureFile) {
		GLint width, height;// Load image, create texture and generate mipmaps
		GLubyte* image = SOIL_load_image(textureFile, &width, &height, 0, SOIL_LOAD_RGB);
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

void SimpleModel::RenderModel()
{
	if (currentTexture)
		glBindTexture(GL_TEXTURE_2D, currentTexture);
	renderer->RenderTransform(transform);
	renderer->RenderVertices();
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
	vertices = _vert;
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

