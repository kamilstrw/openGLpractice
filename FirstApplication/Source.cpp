#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) //?GLFW ��� �������� ��� ������� ��� ������� �� ����� ���� �� ������?
{
	//������ �� ��������
	//��� ������� �� esc ���� �����������
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
	glfwInit();
	//��������� GLFW
	//�������� ����������� ��������� ������ OpenGL. 
	//�������� 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//��������
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//��������� �������� ��� �������� ��������� ��������
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//���������� ����������� ��������� ������� ����
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	//������������� ����
	GLFWwindow* window = glfwCreateWindow(800, 600, "KAMIL TEST", nullptr, nullptr);
	if (window == nullptr)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//������������� GLEW ��� ����������� ������������� ������� OpenGL
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cout << "Failed to initialize GLEW" << endl;
		return -1;
	}


	//������� ������� ��������� 
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0,/*������ ����� ���� x y*/ width, height/*��������� �� ������ � ������ x y*/);

	//�������� �������� ����
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents(); //�������� �� ����� ������� ���������� ��� ����, ���� ���� �� ������. � ������� �������� ������� �������
		
		//������� ������
		glClearColor(0.3f, 0.3f, 0.3f, 0.1f); //���� ������� ���� �� ��������� (�������, �������, �����, ������������)
		

		GLfloat vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f
		};

		GLuint VBO;
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


		glClear(GL_COLOR_BUFFER_BIT); //������� ����

		glfwSwapBuffers(window); //?���������� �����������?

		glfwSetKeyCallback(window, key_callback);//������� �� ������� �������
	}

	glfwTerminate();//������� ���������� ��������
	return 0; 
}