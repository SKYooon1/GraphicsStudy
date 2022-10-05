#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>
#include <random>

#define WINDOW_NAME "practice4"
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

static float bgRed{ 0.1f }, bgGreen{ 0.1f }, bgBlue{ 0.1f };
static int count{};
static bool changeSize{};

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> urd(0, 1);

class Box
{
private:
	float ox_, oy_;					// original pos
	float x_, y_;					// pos
	float width_, height_;			// size
	float red_, green_, blue_;		// rgb
	float velocityX_, velocityY_;	// velocity
	bool isPrinted_;				// is printed
	bool sizeChanged_;				// size up or down
	char moveHow_;					// How to move
public:
	Box() : x_{}, y_{}, width_{ 0.1f }, height_{ 0.1f },
		red_{ urd(gen) }, green_{ urd(gen) }, blue_{ urd(gen) },
		velocityX_{ width_ * urd(gen) / 10 }, velocityY_{ height_ * urd(gen) / 10 },
		isPrinted_{}, sizeChanged_{ true }, moveHow_{}
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
		setOriginalPos(0, 0);
		setSize(0.1f, 0.1f);
		setRgb(urd(gen), urd(gen), urd(gen));
		setVelocityX(width_ * urd(gen) / 10);
		setVelocityY(height_ * urd(gen) / 10);
		setPrinted(false);
		setSizeChanged(false);
		setMoveHow(false);
	}

	float getOriginalX()	const { return ox_; }
	float getOriginalY()	const { return oy_; }
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
	float getVelocityX()	const { return velocityX_; }
	float getVelocityY()	const { return velocityY_; }
	bool getPrinted()		const { return isPrinted_; }
	bool getSizeChange()	const { return sizeChanged_; }
	char getMoveHow()		const { return moveHow_; }

	void setOriginalPos(const float x, const float y)
	{
		ox_ = x;
		oy_ = y;
		x_ = ox_;
		y_ = oy_;
	}
	void setPos(const float x, const float y)
	{
		x_ = x;
		y_ = y;

		if (moveHow_ == 'd')
		{
			if (x - width_ <= -1 || x + width_ >= 1)
				velocityX_ = -velocityX_;
			if (y - height_ <= -1 || y + height_ >= 1)
				velocityY_ = -velocityY_;
		}
		else if (moveHow_ == 'z')
		{
			if (x - width_ <= -1 || x + width_ >= 1)
			{
				velocityX_ = -velocityX_;
				if (velocityY_ >= 0)
					y_ = y + height_;
				else y_ = y - height_;
			}
			if (y - height_ <= -1)
			{
				y_ = y + height_;
				velocityY_ = -velocityY_;
			}
			else if (y + height_ >= 1)
			{
				y_ = y - height_;
				velocityY_ = -velocityY_;
			}
		}
	}
	void setSize(const float w, const float h)
	{
		width_ = w; height_ = h;
	}
	void setRgb(const float r, const float g, const float b)
	{
		red_ = r; green_ = g; blue_ = b;
	}

	void setVelocityX(const float velocity) { velocityX_ = velocity; }

	void setVelocityY(const float velocity) { velocityY_ = velocity; }

	void setPrinted(const bool isPrinted) { isPrinted_ = isPrinted; }

	void setSizeChanged(const bool sizeChanged) { sizeChanged_ = sizeChanged; }

	void setMoveHow(const char move) { moveHow_ = move; }

};

static Box rectangles[5]{};

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
	
	glutDisplayFunc(drawScene);		// 출력 함수 지정
	glutReshapeFunc(reshape);		// 다시 그리기 함수 지정
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseDrag);
	glutTimerFunc(10, timer, 1);

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
	case 'a': case 'A':
		for (Box& r : rectangles)
			if (r.getMoveHow() != 'd')
				r.setMoveHow('d');
			else r.setMoveHow({});
		break;
	case 'i': case 'I':
		for (Box& r : rectangles)
			if (r.getMoveHow() != 'z')
				r.setMoveHow('z');
			else r.setMoveHow({});
		break;
	case 'c': case 'C':
		changeSize = !changeSize;
		break;
	case 's': case 'S':
		for (Box& r : rectangles)
			r.setMoveHow({});
		break;
	case 'm': case 'M':
		for (Box& r : rectangles)
			r.setPos(r.getOriginalX(), r.getOriginalY());
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

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		rectangles[count].setPrinted(true);
		rectangles[count].setOriginalPos(ox, oy);
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
	for (Box& r : rectangles)
	{
		if (r.getMoveHow() == 'd')
			r.setPos(r.getX() + r.getVelocityX(), r.getY() + r.getVelocityY());

		if (r.getMoveHow() == 'z')
			r.setPos(r.getX() + r.getVelocityX(), r.getY());

		if (changeSize)
		{
			if (r.getSizeChange())
				r.setSize(r.getWidth() + 0.001f, r.getHeight() + 0.001f);
			else r.setSize(r.getWidth() - 0.001f, r.getHeight() - 0.001f);
			if (r.getWidth() >= 0.25f || r.getHeight() >= 0.25f)
				r.setSizeChanged(false);
			else if (r.getWidth() <= 0.05f || r.getHeight() <= 0.05f)
				r.setSizeChanged(true);
		}

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
