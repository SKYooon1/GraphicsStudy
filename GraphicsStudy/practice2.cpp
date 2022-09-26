#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>
#include <random>

#define WINDOW_NAME "practice2"
#define WINDOW_POS_X 100
#define WINDOW_POS_Y 100
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

GLvoid drawScene(GLvoid);							// 그리기 콜백함수
GLvoid reshape(int w, int h);						// 다시 그리기 콜백 함수
GLvoid keyboard(unsigned char key, int x, int y);	// 키보드 콜백 함수
GLvoid mouse(int button, int state, int x, int y);

static float red{ 1 }, green{ 1 }, blue{ 1 };
static float boxRed{}, boxGreen{}, boxBlue{};
static float boxWidth{0.25}, boxHeight{0.25};
static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> urd(0, 1);
bool isTimer{};

void main(int argc, char** argv)
{
	// 윈도우 생성
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);	// 윈도우의 위치 설정
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);	// 윈도우의 크기 지정
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
	glutMouseFunc(mouse);

	glutMainLoop();					// 이벤트 처리 시작
}

GLvoid drawScene(GLvoid)
{
	glClearColor(red, green, blue, 1.0f);	// 바탕색 지정
	glClear(GL_COLOR_BUFFER_BIT);			// 설정된 색으로 전체 칠하기

	glColor3f(boxRed, boxGreen, boxBlue);
	glRectf(-boxWidth, -boxHeight, boxWidth, boxHeight);

	glutSwapBuffers();		// 화면에 출력
}

GLvoid reshape(int w, int h)
{
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

GLvoid mouse(int button, int state, int x, int y)
{
	constexpr float w{ WINDOW_WIDTH };
	constexpr float h{ WINDOW_HEIGHT };
	const float ox{ (static_cast<float>(x) - (w / 2.0f)) * (1.0f / (w / 2.0f)) };
	const float oy{ -(static_cast<float>(y) - (h / 2.0f)) * (1.0f / (h / 2.0f)) };

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (ox >= -boxWidth && ox <= boxWidth && oy >= -boxHeight && oy <= boxHeight)
		{	// 상자 안 색 변화
			boxRed = urd(gen);
			boxGreen = urd(gen);
			boxBlue = urd(gen);
		}
		else	// 상자 밖 색 변화
		{
			red = urd(gen);
			green = urd(gen);
			blue = urd(gen);
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if (ox >= -boxWidth && ox <= boxWidth && oy >= -boxHeight && oy <= boxHeight)
		{	// 상자 안 - 크기 확대
			boxWidth = 0.5;
			boxHeight = 0.5;
		}
		else	// 상자 밖 - 크기 축소
		{
			boxWidth = 0.25;
			boxHeight = 0.25;
		}
	}
	glutPostRedisplay();
}
