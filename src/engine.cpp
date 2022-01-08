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
    width = 1280;
    height = 720;
    if(!initGLFW()){
        std::cout << "Failed to initialize GLFW" << std::endl;
        return false;
    }
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    window = glfwCreateWindow(width,height,"DEngine", NULL, NULL);
    if(!window){
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);

    if (!initGLAD())
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    
    vec = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    std::cout << vec.x << vec.y << vec.z << std::endl;
    return true;
}

void Engine::mainLoop() 
{
    while (glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && !glfwWindowShouldClose(window))
    {
        input();
        processEvents();
        draw();
    }
    cleanUp();
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
    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
        width = 1920;
        height = 1080;
        setFullScreen();
    }
    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
        width = 1280;
        height = 720;
        setWindowedScreen();
    }
    if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS){
        width = 768;
        height = 576;
        setWindowedScreen();
    }


}

void Engine::processEvents()
{
}

void Engine::setFullScreen()
{
    glfwSetWindowMonitor(window,glfwGetPrimaryMonitor(),0,0,1920,1080,0);
}
void Engine::setWindowedScreen()
{
    //glfwSetWindowMonitor(window,glfwGetPrimaryMonitor(),0,0,1920,1080,30);
    glfwSetWindowMonitor(window,NULL,10,50,width,height,0);
    glfwMakeContextCurrent(window);
}

void Engine::draw()
{


    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
}