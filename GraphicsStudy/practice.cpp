#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>
#include <random>

#define WINDOW_NAME "practice4"
#define WINDOW_POS_X 100
#define WINDOW_POS_Y 100

GLvoid drawScene(GLvoid);								// �׸��� �ݹ��Լ�
GLvoid reshape(int w, int h);							// �ٽ� �׸��� �ݹ� �Լ�
GLvoid keyboard(unsigned char key, int x, int y);		// Ű���� �ݹ� �Լ�
GLvoid mouseClick(int button, int state, int x, int y);	// ���콺 Ŭ�� �ݹ� �Լ�
GLvoid mouseDrag(int x, int y);							// ���콺 �巡�� �ݹ� �Լ�
GLvoid timer(int value);								// Ÿ�̸� �ݹ� �Լ�

void convertCoordWinToGl(const int x, const int y, float& ox, float& oy);
void convertCoordGlToWin(const float x, const float y, int& ox, int& oy);

static int windowWidth{ 800 };
static int windowHeight{ 600 };

static float bgRed{ 0.1f }, bgGreen{ 0.1f }, bgBlue{ 0.1f };
static int count{};
static bool isMoved{};

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
	float velocityX_, velocityY_;	// velocity
public:
	Box() : x_{}, y_{}, width_{ 0.1f }, height_{ 0.1f },
		red_{ urd(gen) }, green_{ urd(gen) }, blue_{ urd(gen) },
		isPrinted_{}, velocityX_{ width_ * urd(gen) / 10 }, velocityY_{ height_ * urd(gen) / 10 }
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
	bool isPrinted()	const { return isPrinted_; }
	float getVelocityX()	const { return velocityX_; }
	float getVelocityY()	const { return velocityY_; }

	void setSize(const float w, const float h)
	{
		width_ = w; height_ = h;
	}
	void setPos(const float x, const float y)
	{
		x_ = x;
		y_ = y;

		if (x - width_ <= -1 || x + width_ >= 1)
			velocityX_ = -velocityX_;
		if (y - height_ <= -1 || y + height_ >= 1)
			velocityY_ = -velocityY_;
	}
	void setRgb(const float r, const float g, const float b)
	{
		red_ = r; green_ = g; blue_ = b;
	}

	void setPrinted(const bool isPrinted) { isPrinted_ = isPrinted; }

	void setVelocityX(const float velocity) { velocityX_ = velocity; }

	void setVelocityY(const float velocity) { velocityY_ = velocity; }

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
	glutTimerFunc(10, timer, 1);

	glutMainLoop();					// �̺�Ʈ ó�� ����
}

GLvoid drawScene(GLvoid)
{
	glClearColor(bgRed, bgGreen, bgBlue, 1.0f);	// ������ ����
	glClear(GL_COLOR_BUFFER_BIT);			// ������ ������ ��ü ĥ�ϱ�
	
	for (const Box& r : rectangles)
		if (r.isPrinted())
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
		isMoved = !isMoved;
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

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		rectangles[count].setPrinted(true);
		rectangles[count].setPos(ox, oy);
		count++;
		if (count == 5)
			count = 0;
	}

	glutPostRedisplay();
}

GLvoid mouseDrag(int x, int y)
{
	float ox{}, oy{};
	convertCoordWinToGl(x, y, ox, oy);
	
	glutPostRedisplay();
}

GLvoid timer(int value)
{
	if (isMoved)
	{
		for (Box& r : rectangles)
			r.setPos(r.getX() + r.getVelocityX(), r.getY() + r.getVelocityY());

		glutPostRedisplay();
	}
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
