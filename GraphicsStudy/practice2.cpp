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

GLvoid drawScene(GLvoid);							// �׸��� �ݹ��Լ�
GLvoid reshape(int w, int h);						// �ٽ� �׸��� �ݹ� �Լ�
GLvoid keyboard(unsigned char key, int x, int y);	// Ű���� �ݹ� �Լ�
GLvoid timer(int value);
GLvoid mouse(int button, int state, int x, int y);

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
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);			// �������� ��ġ ����
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);		// �������� ũ�� ����
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
	glutMouseFunc(mouse);

	glutMainLoop();					// �̺�Ʈ ó�� ����
}

GLvoid drawScene(GLvoid)
{
	glClearColor(red, green, blue, alpha);	// ������ ����
	glClear(GL_COLOR_BUFFER_BIT);							// ������ ������ ��ü ĥ�ϱ�

	glColor3f(0, 0, 0);
	glRectf(-0.5, -0.5, 0.5, 0.5);

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
		glutTimerFunc(1, timer, 1);
	}
	glutPostRedisplay();
}

GLvoid mouse(int button, int state, int x, int y)
{

}
