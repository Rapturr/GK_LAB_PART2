#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>
#include <glm.hpp>
#include <ext.hpp>
#include <vector>

class primitive{
    std::vector <GLfloat> verticles;
    GLfloat* vert;
    glm::vec3 startPoint;
    glm::vec3  endPoint;
    int count;
    int mode;
    GLuint programID;
    public:
    primitive(){
        count = 0;
    }
    primitive( GLuint programID){
        count = 0;
        this->programID = programID;
    }

    void addPoint(GLfloat x,GLfloat y,int screenX,int screenY){
        verticles.push_back((x/(0.5*screenX))-1);
        verticles.push_back(-((y/(0.5*screenY))-1));
        verticles.push_back(0);
        count += 1;
        vert = verticles.data();
        
    }
    void resetPoints(){
        verticles.clear();
        for(int i=0;i<count*3;i++)
        {
            vert[i] = 0;
            //std::cout<<vert[i]<<std::endl;
        }
        count =0;
    }
    void change_mode(int mode){
        this->mode = mode;
        std::cout<<mode<<std::endl;
    }
    void draw(GLFWwindow* window){
    if(verticles.size() > 5){
        
        
    GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);
        
        

    
    glUseProgram(programID);
    // This will identify our vertex buffer
GLuint vertexbuffer;
// Generate 1 buffer, put the resulting identifier in vertexbuffer
glGenBuffers(1, &vertexbuffer);
// The following commands will talk about our 'vertexbuffer' buffer
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
// Give our vertices to OpenGL.
glBufferData(GL_ARRAY_BUFFER, sizeof(vert)*count*3, vert, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
glVertexAttribPointer(
   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
   3,                  // size
   GL_FLOAT,           // type
   GL_FALSE,           // normalized?
   0,                  // stride
   (void*)0            // array buffer offset
);

            switch(mode)
            {
                case 1:
                    glDrawArrays(GL_POINTS,0,count);
                    break;
                case 2:
                    glDrawArrays(GL_LINES,0,count);
                    break;
                case 3:
                    glDrawArrays(GL_LINE_STRIP,0,count);
                    break;
                case 4:
                    glDrawArrays(GL_LINE_LOOP,0,count);
                    break;
                case 5:
                    glDrawArrays(GL_TRIANGLES,0,count);
                    break;
                case 6:
                    glDrawArrays(GL_TRIANGLE_STRIP,0,count);
                    break;
                case 7:
                    glDrawArrays(GL_TRIANGLE_FAN,0,count);
                    break;
                case 8:
                    glDrawArrays(GL_QUADS,0,count);
                    break;
            }
            glDisableVertexAttribArray(0);
        }   
    }

};