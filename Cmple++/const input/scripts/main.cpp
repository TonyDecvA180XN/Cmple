#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glm/ext.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "socket.h"
#include "windows.h"
#include "stb_image.h"
#include "shader.h"
#include "camera.h"
#include "model.h"
#include "chess.h"
#include "font.h"

using namespace std;

const double pi=2*acos(0.0);

Camera cmrExample(-1.7f,9.0f,4.0f,0.0f,1.0f,0.0f,0.0f,-60.0f);

Shader sdr3DExample;
Shader sdr2DExample;

Model mdlExample;

#include "classes_implementation.h"

void PrepareDisplay3D(){
    glClearColor(0.2f,0.2f,0.2f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    sdr3DExample.use();
    sdr3DExample.setVec3("dirLight.direction", -0.3f, -1.0f, -0.0f);
    sdr3DExample.setVec3("dirLight.ambient", 0.2f, 0.2, 0.2);
    sdr3DExample.setVec3("dirLight.diffuse", 0.7f, 0.7f, 0.7f);
    sdr3DExample.setVec3("dirLight.specular", 0.2f, 0.2f, 0.2f);
    glm::mat4 projection=glm::perspective(glm::radians(cmrExample.Zoom),(float)640/(float)480,0.1f,100.0f);
    glm::mat4 view=cmrExample.GetViewMatrix();
    glm::mat4 model=glm::mat4(1.0f);
    sdr3DExample.setMat4("projection",projection);
    sdr3DExample.setMat4("view",view);
    sdr3DExample.setMat4("model",model);
}

void Display3D(){
    glm::mat4 model=glm::mat4(1.0f);

    mdlExample.Draw(0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,1.0f,sdr3DExample,model);
#include "classes_display_3d.h"
}

void PrepareDisplay2D(){
    glDisable(GL_DEPTH_TEST);

    sdr2DExample.use();
    glm::mat4 projection=glm::mat4(1.0f);
    glm::mat4 view=glm::ortho(0.0f,640.0f,480.0f,0.0f);
    glm::mat4 model=glm::mat4(1.0f);
    sdr2DExample.setMat4("projection",projection);
    sdr2DExample.setMat4("view",view);
    sdr2DExample.setMat4("model",model);

    shaderText.use();
    shaderText.setMat4("projection",projection);
    shaderText.setMat4("view",view);
    shaderText.setMat4("model",model);
}

void Display2D(){

#include "classes_display_2d.h"
}

void Display(){
    PrepareDisplay3D();
    Display3D();
    PrepareDisplay2D();
    Display2D();

    glutSwapBuffers();
}

void TimerDisplay(int n){
    glutPostRedisplay();

#include "classes_update.h"

    glutTimerFunc(10,TimerDisplay,0);
}

void PassiveMouseMove(int x,int y){
}

void MouseButton(int button,int state,int x,int y){

}

void Keyboard(unsigned char key,int x,int y){

}

void LoadResources(){
    initFont();
}

int main(int argc,char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(640,480);
    glutCreateWindow("Example");

    glutDisplayFunc(Display);
    glutTimerFunc(1,TimerListen,0);
    glutTimerFunc(10,TimerDisplay,0);
    glutPassiveMotionFunc(PassiveMouseMove);
    glutMouseFunc(MouseButton);
    glutKeyboardFunc(Keyboard);

    glewInit();

    LoadResources();

    glutMainLoop();

    return 0;
}
