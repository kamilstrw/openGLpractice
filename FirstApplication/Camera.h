#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <iostream> 

class Camera
{
public:
	float lastFrame = 0.0f;
	float yaw = 0, pitch = 0;
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	Camera();
	~Camera();
	void handleInput(GLFWwindow * window);
	void handleMouseInput(double xpos, double ypos);
	glm::mat4 getView();
};
#endif

