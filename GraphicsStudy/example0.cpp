#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>

/* ��ǥ�� ��ȯ�� glm �������
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
*/

GLvoid drawScene(GLvoid);		// �׸��� �ݹ��Լ�
GLvoid reshape(int w, int h);	// �ٽ� �׸��� �ݹ� �Լ�

void main(int argc, char** argv)
{
	// ������ ����
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);			// �������� ��ġ ����
	glutInitWindowSize(250, 250);		// �������� ũ�� ����
	glutCreateWindow("Example0");				// ������ ����("������ �̸�")

	// GLEW �ʱ�ȭ
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)	// glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else std::cout << "GLEW initialized" << std::endl;

	glutDisplayFunc(drawScene);		// ��� �Լ� ����
	glutReshapeFunc(reshape);		// �ٽ� �׸��� �Լ� ����
	glutMainLoop();					// �̺�Ʈ ó�� ����

}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);	// ������ ����
	glClear(GL_COLOR_BUFFER_BIT);							// ������ ������ ��ü ĥ�ϱ�

	// �׸��� ������ �κ�

	glutSwapBuffers();		// ȭ�鿡 ���
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}
