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

class Shader {
public:
	Shader();

	GLvoid makeVertexShader();
	GLvoid makeFragmentShader();
	GLvoid makeShader(const char* shaderName);
	GLvoid makeShaderProgram();
	void isSucceeded();
	void isSucceeded(GLuint shader, const char* name);

	GLuint getId()	const { return id_; }

private:
	GLuint id_;
	GLuint vertex_;
	GLuint fragment_;
};

Shader::Shader() : id_{}, vertex_{}, fragment_{}
{}

void Shader::isSucceeded() {
	GLint result;
	glGetProgramiv(id_, GL_LINK_STATUS, &result);

	if (!result)
	{
		GLchar errorLog[512];
		glGetProgramInfoLog(id_, 512, nullptr, errorLog);
		std::cerr << "ERROR: Shader program ���� ����" << std::endl << errorLog << std::endl;
	}
}

void Shader::isSucceeded(GLuint shader, const char* name) {
	GLint result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		GLchar errorLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, errorLog);
		std::cerr << "ERROR: " << name << " ������ ����" << std::endl << errorLog << std::endl;
	}
}

GLvoid Shader::makeVertexShader() {
	const char* vertexShader{ "vertexShader.glsl" };
	GLchar* vertexSource = readFile(vertexShader);

	vertex_ = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_, 1, &vertexSource, nullptr);
	glCompileShader(vertex_);

	isSucceeded(vertex_, vertexShader);
}

GLvoid Shader::makeFragmentShader() {
	const char* fragmentShader{ "fragmentShader.glsl" };
	GLchar* fragmentSource = readFile(fragmentShader);

	fragment_ = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_, 1, &fragmentSource, nullptr);
	glCompileShader(fragment_);

	isSucceeded(fragment_, fragmentShader);
}

GLvoid Shader::makeShaderProgram() {
	id_ = glCreateProgram();

	glAttachShader(id_, vertex_);
	glAttachShader(id_, fragment_);

	glLinkProgram(id_);

	glDeleteShader(vertex_);
	glDeleteShader(fragment_);

	isSucceeded();
}

Shader myShader;

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

	myShader.makeVertexShader();
	myShader.makeFragmentShader();
	myShader.makeShaderProgram();

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

	glUseProgram(myShader.getId());
	
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
