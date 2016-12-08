#include "OpenGLRenderer.h"

struct Character {
	GLuint     TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};

std::map<GLchar, Character> Characters;

OpenGLRenderer::OpenGLRenderer()
{
	
}
OpenGLRenderer::~OpenGLRenderer(){}

void OpenGLRenderer::EnableOpenGL() {

	//*********Collapsed TEXT RENDERING CODE *****************//
	{
		//Load text shader
		textShader = Shader(FileReader::ReadFromFile("textShader.vert").c_str(),
			FileReader::ReadFromFile("textShader.frag").c_str());
		//

		FT_Library ft;
		if (FT_Init_FreeType(&ft))
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

		FT_Face face;
		if (FT_New_Face(ft, "micross.ttf", 0, &face))
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

		FT_Set_Pixel_Sizes(face, 0, 48);

		if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
			std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

		for (GLubyte c = 0; c < 128; c++)
		{
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// Generate texture
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			// Set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// Now store character for later use
			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};
			Characters.insert(std::pair<GLchar, Character>(c, character));
		}

		FT_Done_Face(face);
		FT_Done_FreeType(ft);

		// Configure VAO/VBO for texture quads
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	printf("EnableOpenGL() called\n");

}

void OpenGLRenderer::PrepareToRender()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Enable depth test to prevent some faces from being invisible
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//camera->Render();
}

void OpenGLRenderer::Render()
{
}

void OpenGLRenderer::PostRender()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

void OpenGLRenderer::SetProgram(GLuint _program)
{
	//program = _program;
	//camera->SetProgram(_program);
	modelHandle = glGetUniformLocation(_program, "model"); // Assign modelHandle to uniform value model in shader program
	viewHandle = glGetUniformLocation(_program, "view");
	projHandle = glGetUniformLocation(_program, "projection");
}

void OpenGLRenderer::Destroy()
{
	// Unbind buffers and arrays to clear memory
	glDeleteBuffers(1, &VBO);
	glDisableVertexAttribArray(0);
	glDeleteVertexArrays(1, &VAO);
}

void OpenGLRenderer::RenderTransform(glm::mat4 transform)
{
	glUniformMatrix4fv(viewHandle, 1, GL_FALSE, &cam->GetViewMatrix()[0][0]); // Send it to the GLSL file
	glUniformMatrix4fv(projHandle, 1, GL_FALSE, &cam->GetProjMatrix()[0][0]); // Send it to the GLSL file
	glUniformMatrix4fv(modelHandle, 1, GL_FALSE, &transform[0][0]); // Send it to the GLSL file
	//camera->RenderModel(transform);
}

void OpenGLRenderer::RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
	glUniformMatrix4fv(glGetUniformLocation(textShader.GetProgram(), "projection"), 1, GL_FALSE, &projection[0][0]);
	// Activate corresponding render state		
	textShader.Use();
	glUniform3f(glGetUniformLocation(textShader.GetProgram(), "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat verts[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLRenderer::SetActiveCamera(Camera & cam)
{
	camera = &cam;
}

Camera* OpenGLRenderer::GetActiveCamera()
{
	return camera;
}








