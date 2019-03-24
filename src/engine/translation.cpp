#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "headers/translation.h"


Translation::Translation(Point p): Transformation(p) {}

Translation::~Translation() {}

void Translation::transform(){
    glTranslatef(this->V().X(), this->V().Y(), this->V().Z());
}