#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>
#include <glm.hpp>
#include <ext.hpp>

class primitive{
    //float vert[];
    glm::vec3 startPoint;
    glm::vec3  endPoint;
    int count;
    primitive(){
        
    }

    void draw(int mode,GLFWwindow* window){
        switch(mode)
        {
            case 1:
                glDrawArrays(GL_POINTS,vert,count);
                break;
            case 2:
                glDrawArrays(GL_LINES,vert,count);
                break;
            case 3:
                glDrawArrays(GL_LINE_STRIP,vert,count);
                break;
            case 4:
                glDrawArrays(GL_LINE_LOOP,vert,count);
                break;
            case 5:
                glDrawArrays(GL_TRIANGLES,vert,count);
                break;
            case 6:
                glDrawArrays(GL_TRIANGLE_STRIP,vert,count);
                break;
            case 7:
                glDrawArrays(GL_TRIANGLE_FAN,vert,count);
                break;
            case 8:
                glDrawArrays(GL_QUADS,vert,count);
                break;
        }
    }

}