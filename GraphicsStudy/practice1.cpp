#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>
#include <random>

#define WINDOW_NAME "practice1"

GLvoid drawScene(GLvoid);							// �׸��� �ݹ��Լ�
GLvoid reshape(int w, int h);						// �ٽ� �׸��� �ݹ� �Լ�
GLvoid keyboard(unsigned char key, int x, int y);	// Ű���� �ݹ� �Լ�
GLvoid timer(int value);							// Ÿ�̸� �ݹ� �Լ�

static float red{ 1 }, green{ 1 }, blue{ 1 }, alpha{ 1 };
static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> urd(0, 1);
bool isTimer{};

void main(int argc, char** argv)
{
	// ������ ����
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);			// �������� ��ġ ����
	glutInitWindowSize(800, 600);		// �������� ũ�� ����
	glutCreateWindow(WINDOW_NAME);				// ������ ����("������ �̸�")

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

	glutMainLoop();					// �̺�Ʈ ó�� ����
}

GLvoid drawScene(GLvoid)
{
	glClearColor(red, green, blue, alpha);	// ������ ����
	glClear(GL_COLOR_BUFFER_BIT);							// ������ ������ ��ü ĥ�ϱ�

	// �׸��� ������ �κ�

	glutSwapBuffers();		// ȭ�鿡 ���
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r': case 'R':		// ������
		red = 1; green = 0; blue = 0;
		break;
	case 'g': case 'G':		// �ʷϻ�
		red = 0; green = 1; blue = 0;
		break;
	case 'b': case 'B':		// �Ķ���
		red = 0; green = 0; blue = 1;
		break;
	case 'a': case 'A':		// ������
		red = urd(gen); green = urd(gen); blue = urd(gen);
		break;
	case 'w': case 'W':		// �Ͼ��
		red = 1; green = 1; blue = 1;
		break;
	case 'k': case 'K':		// ������
		red = 0; green = 0; blue = 0;
		break;
	case 't': case 'T':		// Ÿ�̸� ����/����. Ư�� �ð����� ���������� �ٲ��.
		isTimer = !isTimer;
		glutTimerFunc(100, timer, 1);
		break;
	case VK_ESCAPE: case 'q': case 'Q':		// ���α׷� ����
		glutLeaveMainLoop();
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

GLvoid timer(int value)
{
	if (isTimer)
	{
		red = urd(gen); green = urd(gen); blue = urd(gen);
		glutTimerFunc(100, timer, 1);
	}
	glutPostRedisplay();
}
