#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>
#include <random>

#define WINDOW_NAME "practice3"
#define WINDOW_POS_X 100
#define WINDOW_POS_Y 100

GLvoid drawScene(GLvoid);							// �׸��� �ݹ��Լ�
GLvoid reshape(int w, int h);						// �ٽ� �׸��� �ݹ� �Լ�
GLvoid keyboard(unsigned char key, int x, int y);	// Ű���� �ݹ� �Լ�
GLvoid mouseClick(int button, int state, int x, int y);	// ���콺 Ŭ�� �ݹ� �Լ�
GLvoid mouseDrag(int x, int y);						// ���콺 �巡�� �ݹ� �Լ�

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
	glutMotionFunc(mouseDrag);

	glutMainLoop();					// �̺�Ʈ ó�� ����
}

GLvoid drawScene(GLvoid)
{
	glClearColor(bgRed, bgGreen, bgBlue, 1.0f);	// ������ ����
	glClear(GL_COLOR_BUFFER_BIT);			// ������ ������ ��ü ĥ�ϱ�

	glColor3f(rectangle[0].getRed(), rectangle[0].getGreen(), rectangle[0].getBlue());
	glRectf(-rectangle[0].getWidth(), -rectangle[0].getHeight(),
		rectangle[0].getWidth(), rectangle[0].getHeight());

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
