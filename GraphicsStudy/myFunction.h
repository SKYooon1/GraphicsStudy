#pragma once

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <fstream>
#include <iostream>
#include <random>

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> urd(0, 1);

// 파일 읽기
char* readFile(const char*& fileName);

// 윈도우 to GL 좌표 변환
void convertCoordinateWinToGl(const int x, const int y, float& ox, float& oy,
    const int width, const int height);

// 나만의 버텍스 클래스
class Vertex {
public:
	Vertex();
	Vertex(const float x, const float y);
	virtual ~Vertex();

	void reset();
	GLuint initBuffer();

	float getX()		const { return x_; }
	float getY()		const { return y_; }
	float getSize()		const { return size_; }
	float getRed()		const { return red_; }
	float getGreen()	const { return green_; }
	float getBlue()		const { return blue_; }

	void setPos(const float x, const float y);
	void setX(const float x);
	void setY(const float y);
	void setSize(const float s);
	void setRgb(const float r, const float g, const float b);
	void setRed(const float r);
	void setGreen(const float g);
	void setBlue(const float b);

protected:
	float x_, y_;							// pos
	float size_;							// size
	float red_, green_, blue_;				// rgb
	GLuint vao_;								// Vertex Array Object
	std::vector<GLuint> vboPositionVector_;	// Vertex Buffer Object of position
	std::vector<GLuint> vboColorVector_;		// Vertex Buffer Object of color

private:
	static unsigned int totalVertexNum_;	// Total number of vertex
};

class Square : public Vertex {
public:
	Square();
	Square(const float x, const float y);
	~Square();

	GLuint initBuffer();

private:
	static unsigned int totalSquareNum_;
};
