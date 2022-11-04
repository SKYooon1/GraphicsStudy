#include <iostream>
#include "Shader.h"

Shader::Shader() {
	initVertex();
	initFragment();
	initProgram();
}

GLvoid Shader::initVertex() {
	const char* vertexShader{ "vertexShader.glsl" };
	const GLchar* vertexSource{ readFile(vertexShader) };

	vertex_ = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_, 1, &vertexSource, nullptr);
	glCompileShader(vertex_);

	GLint result;
	glGetShaderiv(vertex_, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		GLchar errorLog[512];
		glGetShaderInfoLog(vertex_, 512, nullptr, errorLog);
		std::cerr << "ERROR: Vertex shader 컴파일 실패" << std::endl << errorLog << std::endl;
	}
}

GLvoid Shader::initFragment() {
	const char* fragmentShader{ "fragmentShader.glsl" };
	const GLchar* fragmentSource{ readFile(fragmentShader) };

	fragment_ = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_, 1, &fragmentSource, nullptr);
	glCompileShader(fragment_);

	GLint result;
	glGetShaderiv(fragment_, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		GLchar errorLog[512];
		glGetShaderInfoLog(fragment_, 512, nullptr, errorLog);
		std::cerr << "ERROR: Fragment shader 컴파일 실패" << std::endl << errorLog << std::endl;
	}
}

GLvoid Shader::initProgram() {
	id_ = glCreateProgram();

	glAttachShader(id_, vertex_);
	glAttachShader(id_, fragment_);

	glLinkProgram(id_);

	glDeleteShader(vertex_);
	glDeleteShader(fragment_);

	GLint result;
	glGetProgramiv(id_, GL_LINK_STATUS, &result);

	if (!result)
	{
		GLchar errorLog[512];
		glGetProgramInfoLog(id_, 512, nullptr, errorLog);
		std::cerr << "ERROR: Shader program 연결 실패" << std::endl << errorLog << std::endl;
	}
}
