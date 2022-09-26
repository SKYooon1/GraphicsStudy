#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>
#include <random>

#define WINDOW_NAME "practice2"
#define WINDOW_POS_X 100
#define WINDOW_POS_Y 100

GLvoid drawScene(GLvoid);							// �׸��� �ݹ��Լ�
GLvoid reshape(int w, int h);						// �ٽ� �׸��� �ݹ� �Լ�
GLvoid keyboard(unsigned char key, int x, int y);	// Ű���� �ݹ� �Լ�
GLvoid mouseClick(int button, int state, int x, int y);	// ���콺 Ŭ�� �ݹ� �Լ�

void convertCoordinateWinToGl(const int x, const int y, float& ox, float& oy);

static int windowWidth{ 800 };
static int windowHeight{ 600 };

static float red{ 1 }, green{ 1 }, blue{ 1 };
static float boxRed{}, boxGreen{}, boxBlue{};
static float boxWidth{0.25}, boxHeight{0.25};

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> urd(0, 1);

void main(int argc, char** argv)
{
	// ������ ����
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// ���÷��� ��� ����
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);	// �������� ��ġ ����
	glutInitWindowSize(windowWidth, windowHeight);	// �������� ũ�� ����
	glutCreateWindow(WINDOW_NAME);			// ������ ����("������ �̸�")

	// GLEW �ʱ�ȭ
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)	// glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else std::cout << "GLEW initialized" << std::endl;

	glutDisplayFunc(drawScene);		// ��� �Լ� ����
	glutReshapeFunc(reshape);		// �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseClick);

	glutMainLoop();					// �̺�Ʈ ó�� ����
}

GLvoid drawScene(GLvoid)
{
	glClearColor(red, green, blue, 1.0f);	// ������ ����
	glClear(GL_COLOR_BUFFER_BIT);			// ������ ������ ��ü ĥ�ϱ�

	glColor3f(boxRed, boxGreen, boxBlue);
	glRectf(-boxWidth, -boxHeight, boxWidth, boxHeight);

	glutSwapBuffers();		// ȭ�鿡 ���
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
	case VK_ESCAPE: case 'q': case 'Q':		// ���α׷� ����
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

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (ox >= -boxWidth && ox <= boxWidth && oy >= -boxHeight && oy <= boxHeight)
		{	// ���� �� �� ��ȭ
			boxRed = urd(gen);
			boxGreen = urd(gen);
			boxBlue = urd(gen);
		}
		else	// ���� �� �� ��ȭ
		{
			red = urd(gen);
			green = urd(gen);
			blue = urd(gen);
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if (ox >= -boxWidth && ox <= boxWidth && oy >= -boxHeight && oy <= boxHeight)
		{	// ���� �� - ũ�� Ȯ��
			boxWidth = 0.5;
			boxHeight = 0.5;
		}
		else	// ���� �� - ũ�� ���
		{
			boxWidth = 0.25;
			boxHeight = 0.25;
		}
	}
	glutPostRedisplay();
}

void convertCoordinateWinToGl(const int x, const int y, float& ox, float& oy)
{
	const float w{ static_cast<float>(windowWidth) };
	const float h{ static_cast<float>(windowHeight) };
	ox = { (static_cast<float>(x) - (w / 2.0f)) * (1.0f / (w / 2.0f)) };
	oy = { -(static_cast<float>(y) - (h / 2.0f)) * (1.0f / (h / 2.0f)) };
}
