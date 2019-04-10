#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <vector>

#include "headers/translation.h"


Translation::Translation(): Transformation(Point()) {}

void Translation::addPoint(Point *p) {
        this->pointV.push_back(p);
}


void Translation::addTime(float t) {
        this->time = t;
}

Translation::~Translation() {}

void Translation::transform() {
        //    glTranslatef(this->V().X(), this->V().Y(), this->V().Z());
}
