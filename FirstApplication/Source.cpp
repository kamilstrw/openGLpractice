#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include <SOIL.h>
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
	
	GLfloat vertices[] = {
		// Positions          // Colors           // Texture Coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
	};
	GLuint indices[] = {
		0, 1, 3, 
		1, 2, 3  
	};
	
	int texWidth, texHeight; 
	unsigned char* image = SOIL_load_image("./src/img/wood.jpg", &texWidth, &texHeight, 0, SOIL_LOAD_RGB);

	GLuint VBO, VAO, EBO, texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//������� �������
	glVertexAttribPointer(0 /*������� ���������*/, 3/*������� ���������*/, GL_FLOAT/*���*/, GL_FALSE/*������������ ������*/, 8 * sizeof(GLfloat)/*���*/, (GLvoid*)0/*��������*/);
	glEnableVertexAttribArray(0);
	//���� �������
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//������� ��������
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	
	glBindVertexArray(0);

	
	Shader myShader("./Shaders/MyShader.vs", "./Shaders/MyShader.frag");
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents(); //�������� �� ����� ������� ���������� ��� ����, ���� ���� �� ������. � ������� �������� ������� �������
		
		//������� ������
		glClearColor(0.3f, 0.3f, 0.3f, 0.1f); //���� ������� ���� �� ��������� (�������, �������, �����, ������������)
		glClear(GL_COLOR_BUFFER_BIT); //������� ����
		glBindTexture(GL_TEXTURE_2D, texture);
		myShader.Use();		
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);	

		glfwSwapBuffers(window); //?���������� �����������?

		glfwSetKeyCallback(window, key_callback);//������� �� ������� �������
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();//������� ���������� ��������
	return 0; 
}