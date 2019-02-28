#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <cstdio>


#include <iostream>
#include <vector>

typedef struct point {
    float x;
    float y;
    float z;
} Point;

std::vector<Point> points;

int readPoints(int argc, char* argv[]) {
    if(argc < 2) {
        std::cerr << "Usage: engine <dataset.xml>" << std::endl;
        return 0;
    }
    else {
        // Populate points with data from xml
    }
    return 1;
}

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {
    glColor3f(1,0,1);
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(5.0,5.0,5.0,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);


// put the geometric transformations here


// put drawing instructions here
    glBegin(GL_TRIANGLES);
    for(std::size_t i=0; i<points.size(); ++i){
        //TODO add color to objects
        Point p = points.at(i);
        glVertex3f(p.x,p.y,p.z);
    }
    glEnd();

    // End of frame
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    if(!readPoints(argc,argv)){
        return 0;
    }

// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG@DI-UM");

// Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);


// put here the registration of the keyboard callbacks

//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);


// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}