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

GLvoid drawScene(GLvoid);								// �׸��� �ݹ��Լ�
GLvoid reshape(int w, int h);							// �ٽ� �׸��� �ݹ� �Լ�
GLvoid keyboard(unsigned char key, int x, int y);		// Ű���� �ݹ� �Լ�
GLvoid mouseClick(int button, int state, int x, int y);	// ���콺 Ŭ�� �ݹ� �Լ�
GLvoid mouseDrag(int x, int y);							// ���콺 �巡�� �ݹ� �Լ�
GLvoid timer(int value);								// Ÿ�̸� �ݹ� �Լ�

void makeVertexShader();
void makeFragmentShader();
GLint makeShaderProgram();

void convertCoordWinToGl(const int x, const int y, float& ox, float& oy);
GLchar* readFile(const std::string& fileName);

static GLint windowWidth{ 800 }, windowHeight{ 600 };
GLuint shaderId{};			// ���̴� ���α׷� �̸�
GLuint vertexShader{};		// ���ؽ� ���̴� ��ü
GLuint fragmentShader{};	// �����׸�Ʈ ���̴� ��ü

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
	
	makeVertexShader();
	makeFragmentShader();
	shaderId = makeShaderProgram();

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
		std::cerr << "ERROR: Vertex shader ������ ����" << std::endl << errorLog << std::endl;
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
		std::cerr << "ERROR: Fragment shader ������ ����" << std::endl << errorLog << std::endl;
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
		std::cerr << "ERROR: Shader program ���� ����" << std::endl << errorLog << std::endl;
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
