#ifndef CAMERA_H
#define CAMERA_H
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <ext.hpp>
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtx/vector_angle.hpp>
#include "Shader.hpp"

/**
 * @brief Creates and handles Camera
 * 
 * @param Position position of the camera
 * @param Orientation Orientation of the camera
 * @param Up Up direction of the camera
 * @param firstClick Prevents the camera from jumping around when first clicking left click
 * @param width width of the window
 * @param height height of the window
 * @param speed speed of the camera
 * @param sensitivity sensitivt of the camera
 */
class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	bool firstClick = true;

	// Stores the width and height of the window
	int width;
	int height;

	// Adjust the speed of the camera and it's sensitivity when looking around
	float speed = 0.1f;
	float sensitivity = 100.0f;

	/**
	 * @brief Camera constructor to set up initial values
	 * 
	 * @param width window width
	 * @param height window height
	 * @param position initial camera position
	 */
	Camera(int width, int height, glm::vec3 position);

	
	/**
	 * @brief Updates and exports the camera matrix to the Vertex Shader
	 * 
	 * @param FOVdeg Field of view
	 * @param nearPlane how near can we see
	 * @param farPlane how far can we see
	 * @param shader shader object
	 * @param uniform uniform
	 */
	void Matrix(float FOVdeg, float nearPlane, float farPlane, LShader& shader, const char* uniform);
	
	/**
	 * @brief handles inputs
	 * 
	 * @param window 
	 */
	void Inputs(GLFWwindow* window);
};
#endif