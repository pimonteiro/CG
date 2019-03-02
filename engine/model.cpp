#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "model.h"
#include "point.h"
#include <iostream>

using namespace std;

Model::Model() {
}

void Model::addElement(Point* point) {
    point_vector.push_back(point);
}

vector<Point*> Model::model() {
    return this->point_vector;
}

void Model::draw() {
    vector <Point*>::iterator it;

    glBegin(GL_TRIANGLES);
    glColor3f(1,0,0);

    for(it = this->point_vector.begin(); it != this->point_vector.end(); it++) {
        glVertex3f((*it)->X(),(*it)->Y(),(*it)->Z());
    }
    glEnd();

}
