#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>
#include <fstream>
#include <string>
#include <random>

#define WINDOW_NAME "practice6"
#define WINDOW_POS_X 100
#define WINDOW_POS_Y 100

GLvoid drawScene(GLvoid);								// 그리기 콜백함수
GLvoid reshape(int w, int h);							// 다시 그리기 콜백 함수
GLvoid keyboard(unsigned char key, int x, int y);		// 키보드 콜백 함수
GLvoid mouseClick(int button, int state, int x, int y);	// 마우스 클릭 콜백 함수
GLvoid mouseDrag(int x, int y);							// 마우스 드래그 콜백 함수
GLvoid timer(int value);								// 타이머 콜백 함수

void makeVertexShader();
void makeFragmentShader();
GLint makeShaderProgram();

void convertCoordWinToGl(const int x, const int y, float& ox, float& oy);
GLchar* readFile(const std::string& fileName);

static GLint windowWidth{ 800 }, windowHeight{ 600 };
GLuint shaderId{};			// 세이더 프로그램 이름
GLuint vertexShader{};		// 버텍스 세이더 객체
GLuint fragmentShader{};	// 프래그먼트 세이더 객체

static float bgRed{ 1 }, bgGreen{ 1 }, bgBlue{ 1 };

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> urd(0, 1);

class myVertex
{
private:
	GLfloat x_, y_;					// pos
	GLfloat size_;					// size
	GLfloat red_, green_, blue_;	// rgb
public:
	myVertex() : x_{ -1 + urd(gen) + urd(gen) }, y_{ -1 + urd(gen) + urd(gen)},
		red_{ urd(gen) }, green_{ urd(gen) }, blue_{ urd(gen) }
	{}
	
	void reset()
	{
		setPos(-1 + urd(gen) + urd(gen), -1 + urd(gen) + urd(gen));
		setSize(0.01f);
		setRgb(urd(gen), urd(gen), urd(gen));
	}
	
	GLfloat getRed()			const { return red_; }
	GLfloat getGreen()		const { return green_; }
	GLfloat getBlue()			const { return blue_; }
	GLfloat getX()			const { return x_; }
	GLfloat getY()			const { return y_; }
	
	void setPos(const float x, const float y)
	{
		x_ = x;
		y_ = y;
	}
	void setSize(const float s)
	{
		size_ = s;
	}
	void setRgb(const float r, const float g, const float b)
	{
		red_ = r; green_ = g; blue_ = b;
	}
	
};

bool isAinB(const myVertex& a, const myVertex& b);

static myVertex rectangles[100]{};
static myVertex eraser{};

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
	
	makeVertexShader();
	makeFragmentShader();
	shaderId = makeShaderProgram();

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
		for (myVertex& r : rectangles)
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
	glutTimerFunc(10, timer, 1);
}

void makeVertexShader()
{
	GLchar* vertexSource;
	std::string vertexShaderName{ "vertexShader.glsl" };

	vertexSource = readFile(vertexShaderName);
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);

	if(!result)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, errorLog);
		std::cerr << "ERROR: Vertex shader 컴파일 실패" << std::endl << errorLog << std::endl;
		return;
	}
}

void makeFragmentShader()
{
	GLchar* fragmentSource;
	std::string fragmentShaderName{ "fragmentShader.glsl" };

	fragmentSource = readFile(fragmentShaderName);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);

	if(!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, errorLog);
		std::cerr << "ERROR: Fragment shader 컴파일 실패" << std::endl << errorLog << std::endl;
		return;
	}
}

GLint makeShaderProgram()
{
	GLuint shaderProgramId;
	shaderProgramId = glCreateProgram();

	glAttachShader(shaderProgramId, vertexShader);
	glAttachShader(shaderProgramId, fragmentShader);

	glLinkProgram(shaderProgramId);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLint result;
	GLchar errorLog[512];
	glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(shaderProgramId, 512, nullptr, errorLog);
		std::cerr << "ERROR: Shader program 연결 실패" << std::endl << errorLog << std::endl;
		return false;
	}

	glUseProgram(shaderProgramId);

	return shaderProgramId;
}


void convertCoordWinToGl(const int x, const int y, float& ox, float& oy)
{
	const float w{ static_cast<float>(windowWidth) };
	const float h{ static_cast<float>(windowHeight) };
	ox = { (static_cast<float>(x) - (w / 2.0f)) * (1.0f / (w / 2.0f)) };
	oy = { -(static_cast<float>(y) - (h / 2.0f)) * (1.0f / (h / 2.0f)) };
}

GLchar* readFile(const std::string& fileName)
{
	std::ifstream in;
	std::string str;

	in.open(fileName);

	if (!in.is_open())
	{
		std::cerr << "The file is not exist." << std::endl;
		return {};
	}

	in.seekg(0, std::ios::end);

	const int size = in.tellg();

	in.seekg(0, std::ios::beg);

	str.resize(size);

	in.read(&str[0], size);

	const char* temp{ str.c_str() };
	return const_cast<char*>(temp);
}
