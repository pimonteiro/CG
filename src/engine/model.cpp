#include "headers/model.h"
#include "headers/point.h"
#include <iostream>
#include <random>

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

void Model::addColor(Point* color) {
    colorsV.push_back(color);
}
std::vector<Point*> Model::model() {
    return this->pointsV;
}

void Model::draw() {
    std::vector <Point*>::iterator itP, itC;
    itC = this->colorsV.begin();

    int changeColor {0};

    glBegin(GL_TRIANGLES);
    glColor3f((*itC)->X(), (*itC)->Y(), (*itC)->Z());
    for(itP = this->pointsV.begin(); itP != this->pointsV.end(); itP++) {
        glVertex3f((*itP)->X(), (*itP)->Y(), (*itP)->Z());
        changeColor++;
        if(changeColor==3){
            changeColor = 0;
            itC++;
            glColor3f((*itC)->X(), (*itC)->Y(), (*itC)->Z());
        }
    }
    glEnd();
}
