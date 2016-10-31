#include "ShaderLoader.h"

void ShaderLoader::LoadShader(GLenum shaderType, GLchar* src)
{
	if(program == 0)
		program = glCreateProgram();
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		GLsizei length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		GLchar * msg = new GLchar[length];
		glGetShaderInfoLog(shader, length, &length, msg);

		//lm->Error(std::string("Shader Compilation Failed: ") + std::string(msg), __FILE__, __LINE__);
	}
	glAttachShader(program, shader);
	glDeleteShader(shader);
}

GLuint ShaderLoader::GetProgram() {
	return program;
}
