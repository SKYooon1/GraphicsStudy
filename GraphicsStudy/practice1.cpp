#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>
#include <random>

#define WINDOW_NAME "practice1"

GLvoid drawScene(GLvoid);							// 그리기 콜백함수
GLvoid reshape(int w, int h);						// 다시 그리기 콜백 함수
GLvoid keyboard(unsigned char key, int x, int y);	// 키보드 콜백 함수
GLvoid timer(int value);

float red{ 1 }, green{ 1 }, blue{ 1 }, alpha{ 1 };

void main(int argc, char** argv)
{
	// 윈도우 생성
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);			// 윈도우의 위치 설정
	glutInitWindowSize(800, 600);		// 윈도우의 크기 지정
	glutCreateWindow(WINDOW_NAME);				// 윈도우 생성("윈도우 이름")

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
	glutTimerFunc(100, timer, 1);

	glutMainLoop();					// 이벤트 처리 시작
}

GLvoid drawScene(GLvoid)
{
	glClearColor(red, green, blue, alpha);	// 바탕색 지정
	glClear(GL_COLOR_BUFFER_BIT);							// 설정된 색으로 전체 칠하기

	// 그리기 구현할 부분

	glutSwapBuffers();		// 화면에 출력
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r': case 'R':
		red = 1; green = 0; blue = 0;	// 빨간색
		break;
	case 'g': case 'G':
		red = 0; green = 1; blue = 0;	// 초록색
		break;
	case 'b': case 'B':
		red = 0; green = 0; blue = 1;	// 파란색
		break;
	case 'a': case 'A':
		// 랜덤색
		break;
	case 'w': case 'W':
		red = 1; green = 1; blue = 1;	// 하얀색
		break;
	case 'k': case 'K':
		red = 0; green = 0; blue = 0;	// 검은색
		break;
	case 't': case 'T':
		// 타이머 설정. 특정 시간마다 랜덤색으로 바뀐다.
		break;
	case 's': case 'S':
		// 타이머 종료
		break;
	case 'q': case 'Q':
		glutLeaveMainLoop();	// 프로그램 종료
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

GLvoid timer(int value)
{

}
