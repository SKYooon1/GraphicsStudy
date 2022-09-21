#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>

GLvoid drawScene(GLvoid);							// �׸��� �ݹ��Լ�
GLvoid reshape(int w, int h);						// �ٽ� �׸��� �ݹ� �Լ�
GLvoid keyboard(unsigned char key, int x, int y);	// Ű���� �ݹ� �Լ�
GLvoid timer(int value);

void main(int argc, char** argv)
{
	// ������ ����
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);			// �������� ��ġ ����
	glutInitWindowSize(800, 600);		// �������� ũ�� ����
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
	glutKeyboardFunc(keyboard);
	glutTimerFunc(100, timer, 1);

	glutMainLoop();					// �̺�Ʈ ó�� ����
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	// ������ ����
	glClear(GL_COLOR_BUFFER_BIT);							// ������ ������ ��ü ĥ�ϱ�

	// �׸��� ������ �κ�

	glutSwapBuffers();		// ȭ�鿡 ���
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
		// ������
		break;
	case 'g': case 'G':
		// �ʷϻ�
		break;
	case 'b': case 'B':
		// �Ķ���
		break;
	case 'a': case 'A':
		// ������
		break;
	case 'w': case 'W':
		// �Ͼ��
		break;
	case 'k': case 'K':
		// ������
		break;
	case 't': case 'T':
		// Ÿ�̸� ����. Ư�� �ð����� ���������� �ٲ��.
		break;
	case 's': case 'S':
		// Ÿ�̸� ����
		break;
	case 'q': case 'Q':
		// ���α׷� ����
		break;
	default:
		break;
	}
}

GLvoid timer(int value)
{

}
