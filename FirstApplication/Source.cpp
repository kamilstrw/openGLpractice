#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
using namespace std;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) //?GLFW сам вызывает эту функцию при нажатии на какую либо из клавиш?
{
	//Пример из учебника
	//При нажатии на esc окно закрывается
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
	glfwInit();
	//Настройка GLFW
	//Задается минимальная требуемая версия OpenGL. 
	//Мажорная 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//Минорная
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Установка профайла для которого создается контекст
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Выключение возможности изменения размера окна
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	//Инициализация окна
	GLFWwindow* window = glfwCreateWindow(800, 600, "KAMIL TEST", nullptr, nullptr);
	if (window == nullptr)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Инициализация GLEW для дальнейшего использования функций OpenGL
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cout << "Failed to initialize GLEW" << endl;
		return -1;
	}
	
	//Задание области отрисовки 
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0,/*Нижний левый угол x y*/ width, height/*Отрисовка по ширине и высоте x y*/);
	
	GLfloat vertices[] = {
		// Positions         // Colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Bottom Left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // Top 
	};
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//Позиция вершины
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//Цвет вершины
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	Shader myShader("./Shaders/MyShader.vs", "./Shaders/MyShader.frag");
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents(); //Проверка на вызов событий клавиатуры или мыши, либо чего то другое. В скобках задается функция колбэка
		
		//Заливка экрана
		//glClearColor(0.3f, 0.3f, 0.3f, 0.1f); //Цвет чистого окна по умолчанию (красный, зеленый, синий, прозрачность)
		glClear(GL_COLOR_BUFFER_BIT); //Очистка окна
		
		myShader.Use();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);	

		glfwSwapBuffers(window); //?Обновление изображения?

		glfwSetKeyCallback(window, key_callback);//Реакция на нажатие клавиши
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();//Очистка выделенных ресурсов
	return 0; 
}