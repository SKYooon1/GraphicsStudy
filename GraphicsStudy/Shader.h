#pragma once

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include "myFunction.h"

// ������ ���̴� Ŭ����
class Shader {
public:
	Shader();

	GLvoid makeVertexShader();
	GLvoid makeFragmentShader();
	GLvoid initShader();
	GLvoid makeShaderProgram();
	void isSucceeded();
	void isSucceeded(GLuint shader, const char* name);

	GLuint getId()	const { return id_; }

private:
	GLuint id_;
	GLuint vertex_;
	GLuint fragment_;
};
