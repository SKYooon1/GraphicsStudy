#include "Shader.h"

Shader::Shader() : id_{}, vertex_{}, fragment_{}
{}

GLvoid Shader::initShader() {
	makeVertexShader();
	makeFragmentShader();
	makeShaderProgram();
}

void Shader::isSucceeded() {
	GLint result;
	glGetProgramiv(id_, GL_LINK_STATUS, &result);

	if (!result)
	{
		GLchar errorLog[512];
		glGetProgramInfoLog(id_, 512, nullptr, errorLog);
		std::cerr << "ERROR: Shader program 연결 실패" << std::endl << errorLog << std::endl;
	}
}

void Shader::isSucceeded(GLuint shader, const char* name) {
	GLint result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		GLchar errorLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, errorLog);
		std::cerr << "ERROR: " << name << " 컴파일 실패" << std::endl << errorLog << std::endl;
	}
}

GLvoid Shader::makeVertexShader() {
	const char* vertexShader{ "vertexShader.glsl" };
	GLchar* vertexSource = readFile(vertexShader);

	vertex_ = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_, 1, &vertexSource, nullptr);
	glCompileShader(vertex_);

	isSucceeded(vertex_, vertexShader);
}

GLvoid Shader::makeFragmentShader() {
	const char* fragmentShader{ "fragmentShader.glsl" };
	GLchar* fragmentSource = readFile(fragmentShader);

	fragment_ = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_, 1, &fragmentSource, nullptr);
	glCompileShader(fragment_);

	isSucceeded(fragment_, fragmentShader);
}

GLvoid Shader::makeShaderProgram() {
	id_ = glCreateProgram();

	glAttachShader(id_, vertex_);
	glAttachShader(id_, fragment_);

	glLinkProgram(id_);

	glDeleteShader(vertex_);
	glDeleteShader(fragment_);

	isSucceeded();
}
