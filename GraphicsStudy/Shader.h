#pragma once

#include <gl/glew.h>

// 나만의 셰이더 클래스
class Shader {
public:
	Shader();

	GLvoid initVertex();
	GLvoid initFragment();
	GLvoid initProgram();

	GLuint getID()	const { return id_; }

private:
	GLuint id_;
	GLuint vertex_;
	GLuint fragment_;
};
