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

// 셰이더 관련 함수
void makeVertexShader();		// 버텍스 셰이더 만들기
void makeFragmentShader();		// 프래그먼트 셰이더 만들기
GLint makeShaderProgram();		// 셰이더 프로그램 만들기

GLuint shaderId{};			// 세이더 프로그램 이름
GLuint vertexShader{};		// 버텍스 세이더 객체
GLuint fragmentShader{};	// 프래그먼트 세이더 객체

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

	glUseProgram(shaderId);
	
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
		std::cerr << "ERROR: Vertex shader 컴파일 실패" << std::endl << errorLog << std::endl;
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
