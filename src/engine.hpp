#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <glad/glad.h>
#include <glfw3.h>

#include<filesystem>
#include <iostream>
#include <cstring>
#include <string>

#include <glm.hpp>
#include <ext.hpp>
#include "Shader.hpp"
#include "primitive.cpp"
#include "Camera.hpp"
#include "cube.cpp"
//#include "TGAloader.cpp"
#include <gtx/transform.hpp>


void glfw_error_callback(int error, const char *description);
void glfw_framebuffer_size_callback(GLFWwindow *window, int width, int height);

/**
 * @brief 
 * 
 */
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
	int inputFlag;

	double oldTimeOnRightClick;
	double newTimeOnRightClick;
	double oldTimeOnLeftClick;
	double newTimeOnLeftClick;
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;

	Camera *camera;
	
	//TGAloader *Tex;


	glm::vec4 vec;
	glm::mat4 trans;
	primitive *prim;
	Cube *cube;
	LShader *shader;
	GLuint programID;
public:
	GLFWwindow* window;

	/**
	 * @brief Construct a new Engine object
	 * 
	 */
	Engine();

	/**
	 * @brief Destroy the Engine object
	 * 
	 */
	~Engine();
	
	/**
	 * @brief Construct a new Engine object
	 * 
	 */
	Engine(const Engine &) = delete;

	/**
	 * @brief 
	 * 
	 * @return Engine& 
	 */
	Engine &operator=(const Engine &) = delete;

	/**
	 * @brief 
	 * 
	 */
	void run();
};
#endif
