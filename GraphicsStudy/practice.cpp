#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>
#include <random>

#define WINDOW_NAME "practice3"
#define WINDOW_POS_X 100
#define WINDOW_POS_Y 100

GLvoid drawScene(GLvoid);								// �׸��� �ݹ��Լ�
GLvoid reshape(int w, int h);							// �ٽ� �׸��� �ݹ� �Լ�
GLvoid keyboard(unsigned char key, int x, int y);		// Ű���� �ݹ� �Լ�
GLvoid mouseClick(int button, int state, int x, int y);	// ���콺 Ŭ�� �ݹ� �Լ�
GLvoid mouseDrag(int x, int y);							// ���콺 �巡�� �ݹ� �Լ�

void convertCoordWinToGl(const int x, const int y, float& ox, float& oy);
void convertCoordGlToWin(const float x, const float y, int& ox, int& oy);

static int windowWidth{ 800 };
static int windowHeight{ 600 };

static float bgRed{ 1 }, bgGreen{ 1 }, bgBlue{ 1 };
static bool leftButton{};
static int count{};

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> urd(0, 1);

class Box
{
private:
	float x_, y_;					// pos
	float width_, height_;			// size
	float red_, green_, blue_;		// rgb
	bool isClicked_;
public:
	Box() : x_{}, y_{}, width_{ 0.25 }, height_{ 0.25 },
		red_{ urd(gen) }, green_{ urd(gen) }, blue_{ urd(gen) }
	{}

	bool isPtInBox(const float& x, const float& y)	const
	{
		if (x >= x_ - width_ && y <= y_ + height_ &&
			x <= x_ + width_ && y >= y_ - height_)
			return true;
		else return false;
	}

	float getWidth()	const { return width_; }
	float getHeight()	const { return height_; }
	float getRed()		const { return red_; }
	float getGreen()	const { return green_; }
	float getBlue()		const { return blue_; }
	float getX()		const { return x_; }
	float getY()		const { return y_; }
	float getLeft()		const { return x_ - width_; }
	float getTop()		const { return y_ + height_; }
	float getRight()	const { return x_ + width_; }
	float getBottom()	const { return y_ - height_; }
	bool isClicked()	const { return isClicked_; }

	void setSize(const float w, const float h)
	{
		width_ = w; height_ = h;
	}
	void setPos(const float x, const float y)
	{
		x_ = x;
		y_ = y;
	}
	void setRgb(const float r, const float g, const float b)
	{
		red_ = r; green_ = g; blue_ = b;
	}
	void setClicked(const bool isClicked) { isClicked_ = isClicked; }

};

static Box rectangles[5]{};

void main(int argc, char** argv)
{
	// ������ ����
	glutInit(&argc, argv);	// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// ���÷��� ��� ����
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);	// �������� ��ġ ����
	glutInitWindowSize(windowWidth, windowHeight);	// �������� ũ�� ����
	glutCreateWindow(WINDOW_NAME);	// ������ ����("������ �̸�")

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

	for (const Box& r : rectangles)
	{
		glColor3f(r.getRed(), r.getGreen(), r.getBlue());
		glRectf(r.getLeft(), r.getTop(),
			r.getRight(), r.getBottom());
	}
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
	case 'a': case 'A':
		rectangles[count].setPos(0, 0);
		count++;
		if (count == 5)
			count = 0;
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

	for (Box& r : rectangles)
		if (button == GLUT_LEFT_BUTTON && r.isPtInBox(ox, oy))
			r.setClicked(true);
		else r.setClicked(false);
	
	glutPostRedisplay();
}

GLvoid mouseDrag(int x, int y)
{
	float ox{}, oy{};
	convertCoordWinToGl(x, y, ox, oy);

	for (Box& r : rectangles)
		if (r.isClicked() && r.isPtInBox(ox, oy))
			r.setPos(ox, oy);

	glutPostRedisplay();
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
