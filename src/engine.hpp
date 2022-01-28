#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>
#include <glm.hpp>
#include <ext.hpp>
#include "Shader.cpp"
#include "primitive.cpp"
#include "Camera.hpp"
#include "cube.cpp"
#include <gtx/transform.hpp>


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
	int stan;

	double oldTimeOnRightClick;
	double newTimeOnRightClick;
	double oldTimeOnLeftClick;
	double newTimeOnLeftClick;
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;

	//Camera Variables
	/*glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::vec3 cameraDirection;
	glm::vec3 up;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;
	glm::mat4 view;*/
	Camera camera;
	

	glm::vec4 vec;
	glm::mat4 trans;
	primitive *prim;
	Cube *cube;
	LShader *shader;
	GLuint programID;
public:
	GLFWwindow* window;

	Engine();
	~Engine();
	
	Engine(const Engine &) = delete;
	Engine &operator=(const Engine &) = delete;


	void run();
};
#endif
