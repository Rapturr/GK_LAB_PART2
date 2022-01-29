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
 * @brief Engine is the core class of the program
 * @param width the width of the screen
 * @param height the height of the screen
 * @param stan unused!!!
 * @param inputFlag unused!!!
 * @param oldTimeOnRightClick helps to measure time between clicks
 * @param newTimeOnRightClick helps to measure time between clicks
 * @param oldTimeOnLeftClick helps to measure time between clicks
 * @param newTimeOnLeftClick helps to measure time between clicks
 * @param deltaTime unused, but we planned to use it
 * @param lastFrame unused, but we planned to use it
 * @param camera camera object
 * @param vec vec matrix
 * @param trans trans matrix
 * @param prim primitive object
 * @param cube cube object
 * @param shader shader object
 * @param programID shader id
 */
class Engine
{
private:

	/**
	 * @brief Initialises GLFW library
	 * 
	 * @return true if succeded
	 * @return false if failed
	 */
	bool initGLFW();

	/**
	 * @brief Initialises GLAD library
	 * 
	 * @return true if succeded
	 * @return false if failed
	 */
	bool initGLAD();

	/**
	 * @brief launches initGLFW() and initGLAD(), gives initial values
	 * 
	 * @return true if succeded
	 * @return false if failed
	 */
	bool init();

	/**
	 * @brief Main loop of the program
	 * 
	 */
	void mainLoop();

	/**
	 * @brief Input handler
	 * 
	 */
	void input();

	/**
	 * @brief Event handler
	 * 
	 */
	void processEvents();

	/**
	 * @brief Clears the screen draws objects
	 * 
	 */
	void draw();

	/**
	 * @brief Destroys objects after closing the window
	 * 
	 */
	void cleanUp();

	/**
	 * @brief Launches window in fullscreen
	 * 
	 */
	void setFullScreen();

	/**
	 * @brief Launches window in windowed mode
	 * 
	 */
	void setWindowedScreen();

	/**
	 * @brief not used. I'm lazy, don't tell Kasia I left it here, she might yell at me
	 * 
	 */
	void setWindowedMode();

	/**
	 * @brief The day she notices I left it here will be my last among the living...
	 * 
	 */
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
	 * @brief initialises the init function and cleanup
	 * 
	 */
	void run();
};
#endif
