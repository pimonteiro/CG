#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>
#include "Point.h"


//Global Variables
std::vector<Point> points;

// Position of the camera around the objects
float camaraAlpha = 0;
float camaraBeta = 0;
int distCam = 5;


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

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();

    float px = distCam*cos(camaraBeta)*cos(camaraAlpha);
    float py = distCam*sin(camaraBeta);
    float pz = distCam*cos(camaraBeta)*sin(camaraAlpha);

    // camera setup
    gluLookAt(px,py,pz,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

	//Loop to draw vertex
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


void processKeys(unsigned char c, int xx, int yy) {
}


void processSpecialKeys(int key, int xx, int yy) {
    if(key == GLUT_KEY_RIGHT){
        camaraAlpha += M_PI/50;
        glutPostRedisplay();
    }
    if(key == GLUT_KEY_LEFT){
        camaraAlpha -= M_PI/50;
        glutPostRedisplay();
    }
    if(key == GLUT_KEY_UP){
        camaraBeta += M_PI/50;
        glutPostRedisplay();
    }
    if(key == GLUT_KEY_DOWN){
        camaraBeta -= M_PI/50;
        glutPostRedisplay();
    }
}


int main(int argc, char **argv) {
    // check if xml with figures is given
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
	
    // Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

    // OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
    // enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
