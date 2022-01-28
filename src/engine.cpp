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

    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    programID = shader->LoadShaders();
    cube = new Cube(programID);
    prim = new primitive(programID);
    /*cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    cameraDirection = glm::normalize(cameraPos - cameraTarget);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    cameraUp = glm::cross(cameraDirection, cameraRight);
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
  		   glm::vec3(0.0f, 0.0f, 0.0f),
  		   glm::vec3(0.0f, 1.0f, 0.0f)
    );*/
    

    if(!initGLFW()){
        std::cout << "Failed to initialize GLFW" << std::endl;
        return false;
    }
    //glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
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
        glm::mat4 view = camera.GetViewMatrix();
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
    fprintf(stderr, "Error1: %s\n", description);
}

void glfw_framebuffer_size_callback(GLFWwindow *window, int width, int height) 
{
    glViewport(0, 0, width, height);
}

/**
 * @brief 
 * 
 */
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
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
        prim->change_mode(1);
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        prim->change_mode(2);
    }
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
        prim->change_mode(3);
    }
    if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
        prim->change_mode(4);
    }
    if(glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS){
        prim->change_mode(5);
    }
    if(glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS){
        prim->change_mode(6);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    newTimeOnRightClick = glfwGetTime();
    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_1) == GLFW_PRESS && (newTimeOnRightClick >= oldTimeOnRightClick + 0.5 || newTimeOnRightClick == 0)){
        oldTimeOnRightClick = newTimeOnRightClick;
        double xpos, ypos;
        int xScreen, yScreen;
        glfwGetWindowSize(window,&xScreen,&yScreen);
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout<<"Mouse x: "<<(GLfloat)xpos<<" y: "<<(GLfloat)ypos<<std::endl;
        std::cout<<"Screen x: "<<xScreen<<" y: "<<yScreen<<std::endl;
        std::cout<<"Time: "<<newTimeOnRightClick<<std::endl;
        prim->addPoint((GLfloat)xpos,(GLfloat)ypos,xScreen,yScreen);
    }
    newTimeOnLeftClick = glfwGetTime();
    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_2) == GLFW_PRESS && (newTimeOnLeftClick >= oldTimeOnLeftClick + 0.5 || newTimeOnLeftClick == 0)){
        oldTimeOnLeftClick = newTimeOnLeftClick;
        prim->resetPoints();
    }
}

void Engine::processEvents()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

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
    glClearColor(0.2f, 0.2f, 0.4f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    prim->draw(window);
    glfwSwapBuffers(window);
    glfwPollEvents();
}