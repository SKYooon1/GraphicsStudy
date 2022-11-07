#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include "myFunction.h"

#define WINDOW_NAME "practice6"
#define WINDOW_POS_X 100
#define WINDOW_POS_Y 100

static int windowWidth{ 800 }, windowHeight{ 600 };
static float bgRed{ 0 }, bgGreen{ 0 }, bgBlue{ 1 };

// 콜백 함수
GLvoid drawScene(GLvoid);								// 그리기 콜백함수
GLvoid reshape(int w, int h);							// 다시 그리기 콜백 함수
GLvoid keyboard(unsigned char key, int x, int y);		// 키보드 콜백 함수
GLvoid mouseClick(int button, int state, int x, int y);	// 마우스 클릭 콜백 함수
GLvoid mouseDrag(int x, int y);							// 마우스 드래그 콜백 함수
GLvoid timer(int value);								// 타이머 콜백 함수

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
		std::cerr << "ERROR: Shader program 연결 실패" << std::endl << errorLog << std::endl;
	}
}

void Shader::isSucceeded(GLuint shader, const char* name) {
	GLint result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		GLchar errorLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, errorLog);
		std::cerr << "ERROR: " << name << " 컴파일 실패" << std::endl << errorLog << std::endl;
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

	myShader.makeVertexShader();
	myShader.makeFragmentShader();
	myShader.makeShaderProgram();

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

	glUseProgram(myShader.getId());
	
	glDrawArrays(GL_TRIANGLES, 0, 3);

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
