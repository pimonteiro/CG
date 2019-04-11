#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <vector>
#include "headers/translation.h"

Translation::Translation(): Transformation(Point()) {}

void
Translation::addPoint(Point* p)
{
        this->pointV.push_back(p);
}


Translation::~Translation() {}


void
Translation::transform()
{
        glTranslatef(this->pointV.at(0)->X(), this->pointV.at(0)->Y(), this->pointV.at(0)->Z());

}