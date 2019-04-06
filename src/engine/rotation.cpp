#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "headers/rotation.h"


Rotation::Rotation(Point p, float ang): Transformation(p), angle(ang) {}

Rotation::~Rotation() {}

void
Rotation::transform()
{
        glRotatef(this->angle, this->V().X(), this->V().Y(), this->V().Z());
}