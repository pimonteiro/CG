#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "headers/rotation.h"


Rotation::Rotation(Point p, float ang, float time): Transformation(p), angle(ang), time(time) {}

Rotation::~Rotation() {}

void
Rotation::transform()
{
        angle = (time == 0 ? angle : glutGet(GLUT_ELAPSED_TIME) * 360 / time);
        glRotatef(this->angle, this->V().X(), this->V().Y(), this->V().Z());
}
