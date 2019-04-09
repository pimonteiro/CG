#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "headers/scale.h"


Scale::Scale(Point p): Transformation(p) {}

Scale::~Scale() {}

void
Scale::transform()
{
        glScalef(this->V().X(), this->V().Y(), this->V().Z());
}