#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>

/* 좌표계 변환용 glm 헤더파일
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
*/

GLvoid drawScene(GLvoid);		// 그리기 콜백함수
GLvoid reshape(int w, int h);	// 다시 그리기 콜백 함수

void main(int argc, char** argv)
{
	// 윈도우 생성
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);			// 윈도우의 위치 설정
	glutInitWindowSize(250, 250);		// 윈도우의 크기 지정
	glutCreateWindow("Example0");				// 윈도우 생성("윈도우 이름")

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
	glutMainLoop();					// 이벤트 처리 시작

}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);	// 바탕색 지정
	glClear(GL_COLOR_BUFFER_BIT);							// 설정된 색으로 전체 칠하기

	// 그리기 구현할 부분

	glutSwapBuffers();		// 화면에 출력
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}
