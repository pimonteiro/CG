#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "headers/pointLight.h"
#include "headers/light.h"
#include "../lib/headers/point.h"

PointLight::PointLight(): Light() {}

void PointLight::draw(){
    Point p = this->POS();
    float pos[4] {
        p.X(), p.Y(), p.Z(), 1.0f
    };
    glLightfv(GL_LIGHT0 + this->INDEX(), GL_POSITION, pos);
    glLightfv(GL_LIGHT0 + this->INDEX(), GL_AMBIENT, this->AMB());
    glLightfv(GL_LIGHT0 + this->INDEX(), GL_DIFFUSE, this->COLOR());
  }
