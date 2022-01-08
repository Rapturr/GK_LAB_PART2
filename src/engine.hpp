#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>
#include <glm.hpp>
#include <ext.hpp>

void glfw_error_callback(int error, const char *description);
void glfw_framebuffer_size_callback(GLFWwindow *window, int width, int height);

class Engine
{
private:
	bool initGLFW();
	bool initGLAD();
	bool init();

	void mainLoop();

	void input();
	void processEvents();
	void draw();

	void cleanUp();


	void setFullScreen();
	void setWindowedScreen();
	void setWindowedMode();
	void setWindowSize();
	
	int width;
	int height;

	glm::vec4 vec;
	glm::mat4 trans;

public:
	GLFWwindow* window;

	Engine();
	~Engine();
	
	Engine(const Engine &) = delete;
	Engine &operator=(const Engine &) = delete;


	void run();
};
#endif
