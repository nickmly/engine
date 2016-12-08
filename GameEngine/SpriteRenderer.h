#pragma once
#include "Shader.h"
#include "SOIL.h"
#include "glm.hpp"
#include "gtx\transform.hpp"
class SpriteRenderer
{
public:
	SpriteRenderer(Shader &_shader, const char* path);
	~SpriteRenderer();
	void DrawSprite(glm::vec2 position, glm::vec2 size, GLfloat rotate);
	void initRenderData(const char* path);

	void Triangles(glm::vec2 position, glm::vec2 size, GLfloat rotate, int index);
	void circle();
private:
	Shader shader;
	GLint texture;
	GLint textures[2];
	GLint LoadTextFromFile(const char* path);
	GLuint quadVAO;
	// Initializes and configures the quad's buffer and vertex attributes

};

