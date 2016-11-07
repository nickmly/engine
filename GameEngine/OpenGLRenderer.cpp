#include "OpenGLRenderer.h"
struct Character {
	GLuint     TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};

std::map<GLchar, Character> Characters;


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
	for (int i = 0; i < (int)_vertices.size(); i++) { // Loop through all the vertices in the vector
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
	printf("AssignVertices() called\nNew size of verts: %d\n", getGlobalVertices().size());
}
void OpenGLRenderer::EnableOpenGL() {

	printf("EnableOpenGL() called\n");
	//Load shaders
	ShaderLoader shaderLoader = ShaderLoader();
	shaderLoader.LoadShader(GL_VERTEX_SHADER,
		FileReader::ReadFromFile("shader.vert"));
	shaderLoader.LoadShader(GL_FRAGMENT_SHADER,
		FileReader::ReadFromFile("shader.frag"));
	UseProgram(shaderLoader.GetProgram());
	//	
	ShaderLoader textShaderLoader = ShaderLoader();
	textShaderLoader.LoadShader(GL_VERTEX_SHADER,
		FileReader::ReadFromFile("textShader.vert"));
	textShaderLoader.LoadShader(GL_FRAGMENT_SHADER,
		FileReader::ReadFromFile("textShader.frag"));
	textProgram = textShaderLoader.GetProgram();
	glLinkProgram(textProgram);


	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	FT_Face face;
	if (FT_New_Face(ft, "micross.ttf", 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	FT_Set_Pixel_Sizes(face, 0, 48);

	if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
		std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
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


	//Enable depth test to prevent some faces from being invisible
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	camera = Camera(Camera::PROJECTION, 800, 600, program); // Setup our camera
	camera.fov = 120.0f;
	camera.SetPositionVector(0.0f, -10.0f, 4.0f); // Put camera at this position
	camera.SetTargetVector(0.0f, 0.0f, 0.0f); // Look at this position
	camera.SetUpVector(0.0f, 1.0f, 0.0f); // Camera is pointing up (0,-1,0) for down

	// Generate 3 buffers and store them into an array
	glGenBuffers(4, buffers);
	// Generate a vertex array
	glGenVertexArrays(1, &VAO);

	// Bind the Vertex Array Object first, then bind and set vertex buff`er(s) and attribute pointer(s).
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
	glBindAttribLocation(program, 2, "vtexCoord");
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);

	//Bind text stuff
	glBindBuffer(GL_ARRAY_BUFFER, buffers[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this 
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
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, getGlobalVertices().size());	
	glBindVertexArray(0);
}

void OpenGLRenderer::PrepareToRender()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program);
	camera.Render();
}

void OpenGLRenderer::UseProgram(GLuint _program)
{
	program = _program;
	glLinkProgram(program);
	glUseProgram(program);
}

void OpenGLRenderer::Destroy()
{
	// Unbind buffers and arrays to clear memory
	//glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	//glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
	glDeleteBuffers(4, buffers);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDeleteVertexArrays(4, &VAO);

	glDeleteProgram(program);
	glDeleteProgram(textProgram);

}

void OpenGLRenderer::RenderSimpleModel()
{
}

void OpenGLRenderer::RenderTransform(glm::mat4 transform)
{
	camera.RenderModel(transform);
}

void OpenGLRenderer::RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800.0f), 0.0f, static_cast<GLfloat>(600.0f));
	// Activate corresponding render state		
	glUseProgram(textProgram);
	glUniformMatrix4fv(glGetUniformLocation(textProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
	glUniform3f(glGetUniformLocation(textProgram, "textColor"), color.x, color.y, color.z);
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
		glBindBuffer(GL_ARRAY_BUFFER, buffers[3]);
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

void OpenGLRenderer::ShowText(char * text, float x, float y)
{
	//TTF_Font *font = TTF_OpenFont("micross.ttf", 24);
	//SDL_Color white = { 255,255,255 };
	//SDL_Surface* surf = TTF_RenderText_Solid(font, text, white);

	//Uint8 colors = surf->format->BytesPerPixel;
	//GLenum textureFormat;
	//if (colors == 4) {   // alpha
	//	if (surf->format->Rmask == 0x000000ff)
	//		textureFormat = GL_RGBA;
	//	else
	//		textureFormat = GL_BGRA;
	//}
	//else {             // no alpha
	//	if (surf->format->Rmask == 0x000000ff)
	//		textureFormat = GL_RGB;
	//	else
	//		textureFormat = GL_BGR;
	//}
	//
	//GLuint texture;
	//glGenTextures(1, &texture);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//glTexImage2D(GL_TEXTURE_2D, 0, colors, surf->w, surf->h, 0,
	//	textureFormat, GL_UNSIGNED_BYTE, surf->pixels);

	//const GLfloat quadVertices[] = { -1.0f, 1.0f, 0.0f,
	//	1.0f, 1.0f, 0.0f,
	//	1.0f,-1.0f, 0.0f,
	//	-1.0f,-1.0f, 0.0f
	//};

	//glVertexPointer(3, GL_FLOAT, 0, quadVertices);
	//glDrawArrays(GL_QUADS, 0, 4);


}





