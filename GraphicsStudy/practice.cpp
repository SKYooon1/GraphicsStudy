#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>
#include <random>

#define WINDOW_NAME "practice5"
#define WINDOW_POS_X 100
#define WINDOW_POS_Y 100

GLvoid drawScene(GLvoid);								// 그리기 콜백함수
GLvoid reshape(int w, int h);							// 다시 그리기 콜백 함수
GLvoid keyboard(unsigned char key, int x, int y);		// 키보드 콜백 함수
GLvoid mouseClick(int button, int state, int x, int y);	// 마우스 클릭 콜백 함수
GLvoid mouseDrag(int x, int y);							// 마우스 드래그 콜백 함수
GLvoid timer(int value);								// 타이머 콜백 함수

void convertCoordWinToGl(const int x, const int y, float& ox, float& oy);
void convertCoordGlToWin(const float x, const float y, int& ox, int& oy);

static int windowWidth{ 800 };
static int windowHeight{ 600 };

static float bgRed{ 1 }, bgGreen{ 1 }, bgBlue{ 1 };

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> urd(0, 1);

class Box
{
private:
	float x_, y_;					// pos
	float width_, height_;			// size
	float red_, green_, blue_;		// rgb
	bool isPrinted_;				// is printed
public:
	Box() : x_{ -1 + urd(gen) + urd(gen) }, y_{ -1 + urd(gen) + urd(gen)},
		width_{0.01f}, height_{0.01f},
		red_{ urd(gen) }, green_{ urd(gen) }, blue_{ urd(gen) },
		isPrinted_{true}
	{}

	bool isPtInBox(const float& x, const float& y)	const
	{
		if (x >= x_ - width_ && y <= y_ + height_ &&
			x <= x_ + width_ && y >= y_ - height_)
			return true;
		else return false;
	}

	void reset()
	{
		setPos(-1 + urd(gen) + urd(gen), -1 + urd(gen) + urd(gen));
		setSize(0.01f, 0.01f);
		setRgb(urd(gen), urd(gen), urd(gen));
		setPrinted(true);
	}
	
	float getWidth()		const { return width_; }
	float getHeight()		const { return height_; }
	float getRed()			const { return red_; }
	float getGreen()		const { return green_; }
	float getBlue()			const { return blue_; }
	float getX()			const { return x_; }
	float getY()			const { return y_; }
	float getLeft()			const { return x_ - width_; }
	float getTop()			const { return y_ + height_; }
	float getRight()		const { return x_ + width_; }
	float getBottom()		const { return y_ - height_; }
	bool getPrinted()		const { return isPrinted_; }
	
	void setPos(const float x, const float y)
	{
		x_ = x;
		y_ = y;
	}
	void setSize(const float w, const float h)
	{
		width_ = w; height_ = h;
	}
	void setRgb(const float r, const float g, const float b)
	{
		red_ = r; green_ = g; blue_ = b;
	}
	
	void setPrinted(const bool isPrinted) { isPrinted_ = isPrinted; }
	
};

bool isAinB(const Box& a, const Box& b);

static Box rectangles[100]{};
static Box eraser{};

void main(int argc, char** argv)
{
	// 윈도우 생성
	glutInit(&argc, argv);	// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);	// 윈도우의 위치 설정
	glutInitWindowSize(windowWidth, windowHeight);	// 윈도우의 크기 지정
	glutCreateWindow(WINDOW_NAME);	// 윈도우 생성("윈도우 이름")

	// GLEW 초기화
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)	// glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else std::cout << "GLEW initialized" << std::endl;

	eraser.setSize(0.1f, 0.1f);
	eraser.setRgb(0, 0, 0);
	eraser.setPrinted(false);

	glutDisplayFunc(drawScene);		// 출력 함수 지정
	glutReshapeFunc(reshape);		// 다시 그리기 함수 지정
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseDrag);

	glutMainLoop();					// 이벤트 처리 시작
}

GLvoid drawScene(GLvoid)
{
	glClearColor(bgRed, bgGreen, bgBlue, 1.0f);	// 바탕색 지정
	glClear(GL_COLOR_BUFFER_BIT);			// 설정된 색으로 전체 칠하기
	
	for (const Box& r : rectangles)
		if (r.getPrinted())
		{
			glColor3f(r.getRed(), r.getGreen(), r.getBlue());
			glRectf(r.getLeft(), r.getTop(),
			r.getRight(), r.getBottom());
		}
	if (eraser.getPrinted())
	{
		glColor3f(eraser.getRed(), eraser.getGreen(), eraser.getBlue());
		glRectf(eraser.getLeft(), eraser.getTop(),
			eraser.getRight(), eraser.getBottom());
	}

	glutSwapBuffers();		// 화면에 출력
}

GLvoid reshape(int w, int h)
{
	windowWidth = glutGet(GLUT_WINDOW_WIDTH);
	windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
	glViewport(0, 0, w, h);
}

GLvoid keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case VK_ESCAPE: case 'q': case 'Q':		// 프로그램 종료
		glutLeaveMainLoop();
		break;
	case 'r': case 'R':
		for (Box& r : rectangles)
			r.reset();
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

GLvoid mouseClick(int button, int state, int x, int y)
{
	float ox{}, oy{};
	convertCoordWinToGl(x, y, ox, oy);

	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			eraser.setPos(ox, oy);
			eraser.setPrinted(true);
			for (Box& r : rectangles)
				if (isAinB(r, eraser))	// r이 eraser 안에 들어가면
					r.setPrinted(false);
		}
		else if (state == GLUT_UP)
			eraser.setPrinted(false);
	}

	glutPostRedisplay();
}

GLvoid mouseDrag(int x, int y)
{
	float ox{}, oy{};
	convertCoordWinToGl(x, y, ox, oy);
	
	if (eraser.getPrinted())
	{
		eraser.setPos(ox, oy);
		for (Box& r : rectangles)
			if (isAinB(r, eraser))	// r이 eraser 안에 들어가면
				r.setPrinted(false);
	}
	glutPostRedisplay();
}

GLvoid timer(int value)
{
	glutTimerFunc(10, timer, 1);
}

void convertCoordWinToGl(const int x, const int y, float& ox, float& oy)
{
	const float w{ static_cast<float>(windowWidth) };
	const float h{ static_cast<float>(windowHeight) };
	ox = { (static_cast<float>(x) - (w / 2.0f)) * (1.0f / (w / 2.0f)) };
	oy = { -(static_cast<float>(y) - (h / 2.0f)) * (1.0f / (h / 2.0f)) };
}

void convertCoordGlToWin(const float x, const float y, int& ox, int& oy)
{
	const int w{ windowWidth };
	const int h{ windowHeight };
	
	ox = static_cast<int>((x + 1) / 2 * static_cast<float>(w));
	oy = static_cast<int>(-(y + 1) / 2 * static_cast<float>(h));
}

bool isAinB(const Box& a, const Box& b)
{
	if (a.getLeft() >= b.getLeft() && a.getRight() <= b.getRight() &&	// 수평충돌
		a.getTop() <= b.getTop() && a.getBottom() >= b.getBottom())		// 수직충돌
		return true;
	else return false;
}
