#include "model.h"
#include "point.h"
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

Model::Model() {
}

void Model::addElement(Point* point) {
    pointsV.push_back(point);
}

std::vector<Point*> Model::model() {
    return this->pointsV;
}

void Model::draw() {
    std::vector <Point*>::iterator it;

    glBegin(GL_TRIANGLES);
    glColor3f(1,0,0);
    for(it = this->pointsV.begin(); it != this->pointsV.end(); it++) {
        glVertex3f((*it)->X(),(*it)->Y(),(*it)->Z());
    }
    glEnd();

}
