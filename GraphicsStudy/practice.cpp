#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include "myFunction.h"

#define WINDOW_NAME "practice6"
#define WINDOW_POS_X 100
#define WINDOW_POS_Y 100

static int windowWidth{ 800 }, windowHeight{ 600 };
static float bgRed{ 0 }, bgGreen{ 0 }, bgBlue{ 1 };

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

GLuint shaderId{};			// ���̴� ���α׷� �̸�
GLuint vertexShader{};		// ���ؽ� ���̴� ��ü
GLuint fragmentShader{};	// �����׸�Ʈ ���̴� ��ü

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
	convertCoordinateWinToGl(x, y, ox, oy, windowWidth, windowHeight);

	glutPostRedisplay();
}

GLvoid mouseDrag(int x, int y)
{
	float ox{}, oy{};
	convertCoordinateWinToGl(x, y, ox, oy, windowWidth, windowHeight);
	
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
