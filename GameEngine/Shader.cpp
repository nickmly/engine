#include "Shader.h"



Shader::Shader()
{
}

Shader::Shader(const char* _vertexFile, const char* _fragFile)
{
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);

	//Compile vertex shader
	glShaderSource(vertShader, 1, &_vertexFile, nullptr);
	glCompileShader(vertShader);

	GLint compiled;
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		GLsizei length;
		glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &length);
		GLchar * msg = new GLchar[length];
		glGetShaderInfoLog(vertShader, length, &length, msg);
		std::cout << "Shader compilation failed: " << msg << std::endl;
	}
	//

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Compile fragment shader
	glShaderSource(fragShader, 1, &_fragFile, nullptr);
	glCompileShader(fragShader);

	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		GLsizei length;
		glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &length);
		GLchar * msg = new GLchar[length];
		glGetShaderInfoLog(fragShader, length, &length, msg);
		std::cout << "Shader compilation failed: " << msg << std::endl;
	}
	//

	program = glCreateProgram();

	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked) {
		GLsizei length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		GLchar * msg = new GLchar[length];
		glGetProgramInfoLog(program, length, &length, msg);
		std::cout << "Failed to link shaders: " << msg << std::endl;
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

void Shader::Use() 
{
	glUseProgram(program);
}

GLuint Shader::GetProgram()
{
	return program;
}

Shader::~Shader()
{
	//this doesn't work here, move it to another place
	//glDeleteProgram(program);
}
