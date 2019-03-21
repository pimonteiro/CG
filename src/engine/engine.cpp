#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <vector>
#include "headers/parser.h"
#include "headers/group.h"

using namespace std;

Group* group {new Group};
int axis {0};
float camaraAlpha {0.7};
float camaraBeta {0.5};
float distCam {1500};
GLenum mode;

void changeSize(int w, int h) {
    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;
    // compute window's aspect ratio
    float ratio {w * 1.0f / h};
    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    // Set perspective
    gluPerspective(45.0f,ratio, 2.5f ,2500.0f);
    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void renderScene() {
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float px { static_cast<float>(distCam*cos(camaraBeta)*cos(camaraAlpha)) };
    float py { static_cast<float>(distCam*sin(camaraBeta)) };
    float pz { static_cast<float>(distCam*cos(camaraBeta)*sin(camaraAlpha)) };
    // set the camera
    glLoadIdentity();
    gluLookAt(px,py,pz,
            0.0, 0.0, 0.0,
            0.0f, 1.0f, 0.0f);

    // set axis
    if(axis) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_LINES);
        glColor3f(0, 0, 1);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(10.0f, 0.0f, 0.0f);
        glColor3f(0, 1, 0);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 10.0f, 0.0f);
        glColor3f(1, 0, 0);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 10.0f);
        glEnd();
    }

    GLenum modes[] = {GL_FILL,GL_LINE, GL_POINT};
    glPolygonMode(GL_FRONT, modes[mode]);
    group->draw();
    glutSwapBuffers();
}

void processSpecialKeys(int key, int xx, int yy) {
    if(key == GLUT_KEY_RIGHT){
        camaraAlpha += M_PI/50;
    }
    if(key == GLUT_KEY_LEFT){
        camaraAlpha -= M_PI/50;
    }
    if(key == GLUT_KEY_UP){
        camaraBeta += M_PI/50;
        if(camaraBeta > 1.5f)
            camaraBeta = 1.5f;
    }
    if(key == GLUT_KEY_DOWN){
        camaraBeta -= M_PI/50;
        if(camaraBeta < -1.5f)
            camaraBeta = -1.5f;
    }
    glutPostRedisplay();
}

void processKeys(unsigned char key, int x, int y) {
    if(key == 'a' || key == 'A') {
        axis = !axis;
    }
    if(key == 'c' || key == 'C') {
        mode = (mode + 1) % 3;
    }
    if(key == 'm' || key == 'M') {
        distCam -= 5.0f;
    }
    if(key == 'l' || key == 'L') {
        distCam += 5.0f;
    }
    glutPostRedisplay();
}

void initCostumGL(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Solar System - Group 13");

    // callback registration
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(processKeys);

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glPolygonMode(GL_FRONT, GL_LINE);
}

int main(int argc, char **argv) {
    if(argc == 2) {
        Parser().ReadXML(group, "solarSystem.xml");
        initCostumGL(argc, argv);
        glutMainLoop();
        return 1;
    }
    cerr << "Usage: ./engine <file>.xml" << std::endl;
    return 1;
}