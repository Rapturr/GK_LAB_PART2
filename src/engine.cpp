#include "engine.hpp"

Engine::Engine() 
{
    
}

Engine::~Engine() 
{
    
}

void Engine::run()
{
    if(!init()){
        std::cout<<"Error while initializing!"<<std::endl;
        exit(-1);
    }
    mainLoop();
    cleanUp();

}

bool Engine::initGLFW() 
{
    glfwSetErrorCallback(glfw_error_callback);
    if(!glfwInit()){
        return false;
    }
    window = glfwCreateWindow(1280,720,"DEngine", NULL, NULL);
    if(!window){
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);

    return true;
}

bool Engine::initGLAD() 
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return false;
    }
    return true;
}

bool Engine::init() 
{
    if(!initGLFW()){
        std::cout << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    if (!initGLAD())
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    return true;
}

void Engine::mainLoop() 
{
    while (!glfwWindowShouldClose(window))
    {
        input();
        processEvents();
        draw();
    }
}
void Engine::cleanUp() 
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void glfw_error_callback(int error, const char* description) 
{
    fprintf(stderr, "Error: %s\n", description);
}

void glfw_framebuffer_size_callback(GLFWwindow *window, int width, int height) 
{
    glViewport(0, 0, width, height);
}

void Engine::input()
{
    if(glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS){

    }
}

void Engine::processEvents()
{
}

void Engine::setFullScreen()
{
    //glfwSetWindowMonitor(window,glfwGetPrimaryMonitor(),0,0,1920,1080,30);
    glfwSetWindowMonitor(window,glfwGetPrimaryMonitor(),0,0,mode->width,mode->height,0);
}

void Engine::draw()
{


    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    input();
    glfwSwapBuffers(window);
    glfwPollEvents();
}
