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

// ���� �б�
char* readFile(const char*& fileName);

// ������ to GL ��ǥ ��ȯ
void convertCoordinateWinToGl(const int x, const int y, float& ox, float& oy,
    const int width, const int height);
