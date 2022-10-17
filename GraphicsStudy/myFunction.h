#pragma once

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

class myVertex
{
private:
	float x_, y_;					// pos
	float size_;					// size
	float red_, green_, blue_;	// rgb

public:
	myVertex() : x_{ -1 + urd(gen) + urd(gen) }, y_{ -1 + urd(gen) + urd(gen) },
		red_{ urd(gen) }, green_{ urd(gen) }, blue_{ urd(gen) }
	{}

	void reset()
	{
		setPos(-1 + urd(gen) + urd(gen), -1 + urd(gen) + urd(gen));
		setSize(0.01f);
		setRgb(urd(gen), urd(gen), urd(gen));
	}

	float getRed()			const { return red_; }
	float getGreen()		const { return green_; }
	float getBlue()			const { return blue_; }
	float getX()			const { return x_; }
	float getY()			const { return y_; }

	void setPos(const float x, const float y)
	{
		x_ = x;
		y_ = y;
	}
	void setSize(const float s)
	{
		size_ = s;
	}
	void setRgb(const float r, const float g, const float b)
	{
		red_ = r; green_ = g; blue_ = b;
	}

};
