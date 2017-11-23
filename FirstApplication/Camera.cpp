#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::handleInput(GLFWwindow * window)
{
	float deltaTime = 0.0f;	
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	this->lastFrame = currentFrame;
	float cameraSpeed = 2.5f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		this->cameraPos += cameraSpeed * this->cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		this->cameraPos -= cameraSpeed * this->cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		this->cameraPos -= glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		this->cameraPos += glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		this->cameraPos += this->cameraUp * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		this->cameraPos -= this->cameraUp * cameraSpeed;
}
void Camera::handleMouseInput(double xpos, double ypos)
{
	float deltaTime = 0.0f;
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	this->lastFrame = currentFrame;
	float cameraSpeed = 15.0f * deltaTime;

	this->yaw += xpos*cameraSpeed;
	this->pitch -= ypos*cameraSpeed;

	if (this->pitch > 89.0f)
	{
		this->pitch = 89.0f;
	}
	if (this->pitch < -89.0f)
	{
		this->pitch = -89.0f;
	}
	glm::vec3 front;
	front.x = cos(glm::radians(this->pitch)) * cos(glm::radians(this->yaw));
	front.y = sin(glm::radians(this->pitch));
	front.z = cos(glm::radians(this->pitch)) * sin(glm::radians(this->yaw));
	this->cameraFront = glm::normalize(front);
}
