#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>
#include <fstream>
#include <random>

#define WINDOW_NAME "practice6"
#define WINDOW_POS_X 100
#define WINDOW_POS_Y 100

// �ݹ� �Լ�
GLvoid drawScene(GLvoid);								// �׸��� �ݹ��Լ�
GLvoid reshape(int w, int h);							// �ٽ� �׸��� �ݹ� �Լ�
GLvoid keyboard(unsigned char key, int x, int y);		// Ű���� �ݹ� �Լ�
GLvoid mouseClick(int button, int state, int x, int y);	// ���콺 Ŭ�� �ݹ� �Լ�
GLvoid mouseDrag(int x, int y);							// ���콺 �巡�� �ݹ� �Լ�
GLvoid timer(int value);								// Ÿ�̸� �ݹ� �Լ�

// ���̴� ���� �Լ�
void makeVertexShader();		// ���ؽ� ���̴� �����
void makeFragmentShader();		// �����׸�Ʈ ���̴� �����
GLint makeShaderProgram();		// ���̴� ���α׷� �����

GLchar* readFile(const char*& fileName);		// ���� �б� �Լ�

// ��ǥ ��ȯ �Լ�
void convertCoordWinToGl(const int x, const int y, float& ox, float& oy);

static GLint windowWidth{ 800 }, windowHeight{ 600 };
GLuint shaderId{};			// ���̴� ���α׷� �̸�
GLuint vertexShader{};		// ���ؽ� ���̴� ��ü
GLuint fragmentShader{};	// �����׸�Ʈ ���̴� ��ü

static float bgRed{ 0 }, bgGreen{ 0 }, bgBlue{ 1 };

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> urd(0, 1);

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

	glUseProgram(shaderId);
	
	glDrawArrays(GL_TRIANGLES, 0, 3);

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
	const char* vertexShaderName{ "vertexShader.glsl" };

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
	const char* fragmentShaderName{ "fragmentShader.glsl" };

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

GLchar* readFile(const char*& fileName)
{
	std::ifstream in;
	in.open(fileName);

	if (!in.is_open())
	{
		std::cerr << "The file is not exist." << std::endl;
		return {};
	}

	in.seekg(0, std::ios::end);

	const int size = in.tellg();

	char* buf = new char[size];

	in.seekg(0, std::ios::beg);

	in.read(buf, size);
	
	return buf;
}
