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
