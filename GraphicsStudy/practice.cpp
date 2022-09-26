#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>
#include <random>

#define WINDOW_NAME "practice3"
#define WINDOW_POS_X 100
#define WINDOW_POS_Y 100

GLvoid drawScene(GLvoid);							// 그리기 콜백함수
GLvoid reshape(int w, int h);						// 다시 그리기 콜백 함수
GLvoid keyboard(unsigned char key, int x, int y);	// 키보드 콜백 함수
GLvoid mouseClick(int button, int state, int x, int y);	// 마우스 클릭 콜백 함수
GLvoid mouseDrag(int x, int y);						// 마우스 드래그 콜백 함수

void convertCoordinateWinToGl(const int x, const int y, float& ox, float& oy);

static int windowWidth{ 800 };
static int windowHeight{ 600 };

static float bgRed{ 1 }, bgGreen{ 1 }, bgBlue{ 1 };

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> urd(0, 1);

class Box
{
private:
	float left, top, right, bottom;	// pos
	float width, height;			// size
	float red, green, blue;			// rgb
public:

	Box() : width{ 0.25 }, height{ 0.25 },
		red{ urd(gen) }, green{ urd(gen) }, blue{ urd(gen) }
	{}

	float getWidth()	const { return width; }
	float getHeight()	const { return height; }
	float getRed()		const { return red; }
	float getGreen()	const { return green; }
	float getBlue()		const { return blue; }
	float getLeft()		const { return left; }
	float getTop()		const { return top; }
	float getRight()	const { return right; }
	float getBottom()	const { return bottom; }

	void setSize(const float w, const float h)
	{
		width = w; height = h;
	}
	void setPos(const float l, const float t, const float r, const float b)
	{
		left = l; top = t; right = r; bottom = b;
	}
	void setPos(const float x, const float y)
	{
		left = x - width / 2;
		top = y + height / 2;
		right = x + width / 2;
		bottom = y - height / 2;
	}
	void setRgb(const float r, const float g, const float b)
	{
		red = r; green = g; blue = b;
	}

};

Box rectangle[5]{};

void main(int argc, char** argv)
{
	// 윈도우 생성
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);	// 윈도우의 위치 설정
	glutInitWindowSize(windowWidth, windowHeight);	// 윈도우의 크기 지정
	glutCreateWindow(WINDOW_NAME);			// 윈도우 생성("윈도우 이름")

	// GLEW 초기화
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)	// glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else std::cout << "GLEW initialized" << std::endl;

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

	glColor3f(rectangle[0].getRed(), rectangle[0].getGreen(), rectangle[0].getBlue());
	glRectf(-rectangle[0].getWidth(), -rectangle[0].getHeight(),
		rectangle[0].getWidth(), rectangle[0].getHeight());

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
	default:
		break;
	}
	glutPostRedisplay();
}

GLvoid mouseClick(int button, int state, int x, int y)
{
	float ox{}, oy{};
	convertCoordinateWinToGl(x, y, ox, oy);
	
	glutPostRedisplay();
}

GLvoid mouseDrag(int x, int y)
{
	float ox{}, oy{};
	convertCoordinateWinToGl(x, y, ox, oy);

}

void convertCoordinateWinToGl(const int x, const int y, float& ox, float& oy)
{
	const float w{ static_cast<float>(windowWidth) };
	const float h{ static_cast<float>(windowHeight) };
	ox = { (static_cast<float>(x) - (w / 2.0f)) * (1.0f / (w / 2.0f)) };
	oy = { -(static_cast<float>(y) - (h / 2.0f)) * (1.0f / (h / 2.0f)) };
}
