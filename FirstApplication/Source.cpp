#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include <SOIL.h>
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
	//Позиция вершины
	glVertexAttribPointer(0 /*позиция аргумента*/, 3/*размера аргумента*/, GL_FLOAT/*тип*/, GL_FALSE/*нормализация данных*/, 8 * sizeof(GLfloat)/*шаг*/, (GLvoid*)0/*смещение*/);
	glEnableVertexAttribArray(0);
	//Цвет вершины
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//Позиция текстуры
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	
	glBindVertexArray(0);

	
	Shader myShader("./Shaders/MyShader.vs", "./Shaders/MyShader.frag");
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents(); //Проверка на вызов событий клавиатуры или мыши, либо чего то другое. В скобках задается функция колбэка
		
		//Заливка экрана
		glClearColor(0.3f, 0.3f, 0.3f, 0.1f); //Цвет чистого окна по умолчанию (красный, зеленый, синий, прозрачность)
		glClear(GL_COLOR_BUFFER_BIT); //Очистка окна
		glBindTexture(GL_TEXTURE_2D, texture);
		myShader.Use();		
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);	

		glfwSwapBuffers(window); //?Обновление изображения?

		glfwSetKeyCallback(window, key_callback);//Реакция на нажатие клавиши
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();//Очистка выделенных ресурсов
	return 0; 
}