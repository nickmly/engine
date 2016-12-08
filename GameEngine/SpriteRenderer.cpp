#include "SpriteRenderer.h"


SpriteRenderer::SpriteRenderer(Shader &_shader, const char* path)
{
	shader = _shader;
	initRenderData(path);
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::DrawSprite(glm::vec2 position, glm::vec2 size, GLfloat rotate)
{    //this->shader.Use();
	glDepthMask(GL_FALSE);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back

	model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

	glm::mat4 projection = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f, -0.10f, 1.0f);

	shader.Use();
	glUniformMatrix4fv(glGetUniformLocation(shader.GetProgram(), "projection"), 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader.GetProgram(), "model"), 1, GL_FALSE, &model[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDepthMask(GL_TRUE);

}

void SpriteRenderer::Triangles(glm::vec2 position, glm::vec2 size, GLfloat rotate, int index) {
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back

	model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

	glm::mat4 projection = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f, -0.10f, 1.0f);

	shader.Use();
	glUniformMatrix4fv(glGetUniformLocation(shader.GetProgram(), "projection"), 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader.GetProgram(), "model"), 1, GL_FALSE, &model[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[index]);

	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
void SpriteRenderer::circle(){
#define RES 180
#define RADIUS .5
	GLfloat vertices[(RES + 1) * 2];
	float center_x = 0;  // -.5<->+.5 every 8 seconds
	float center_y = 0;  // -.5<->+.5 every 4 seconds
	for (int ii = 0; ii < 180; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(180);//get the current angle 

		float x = RADIUS * cosf(theta);//calculate the x component 
		float y = RADIUS * sinf(theta);//calculate the y component 

		vertices[ii * 2] = x;
		vertices[ii * 2 + 1] = y;
	} 																	   // circle center
	
	// circle points
	for (int i = 0; i < RES; i++) {
		float angle = 2 * 3.14159 * i / RES;
		GLfloat x = center_x + cos(angle) * RADIUS;
		GLfloat y = center_y + sin(angle) * RADIUS;
		vertices[i * 2] = x;
		vertices[i * 2 + 1] = y;
	}
	GLuint vbo_vertices;
	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// projection matrix to deal with aspect ratio
	glm::mat4 projection = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f, -0.10f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(shader.GetProgram(), "projection"), 1, GL_FALSE,  &projection[0][0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glEnableVertexAttribArray(glGetUniformLocation(shader.GetProgram(), "vTexCoord"));
	glVertexAttribPointer(
		glGetUniformLocation(shader.GetProgram(), "vTexCoord"),  // attribute
		2,                  // number of elements per vertex, here (x,y,z,w)
		GL_FLOAT,           // the type of each element
		GL_FALSE,           // take our values as-is
		0,                  // no extra data between each position
		0                   // offset of first element
	);
	glDrawArrays(GL_TRIANGLES,0, sizeof(vertices));

	glDisableVertexAttribArray(glGetUniformLocation(shader.GetProgram(), "vTexCoord"));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vbo_vertices);

}

GLint SpriteRenderer::LoadTextFromFile(const char * path)
{	//Generate texture ID and load texture data 
	std::string filename = std::string(path);
	//filename = directory + '/' + filename;
	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height;
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	return textureID;
}

void SpriteRenderer::initRenderData(const char* path)
{  // Configure VAO/VBO
	GLuint VBO;
	texture = LoadTextFromFile(path);
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
