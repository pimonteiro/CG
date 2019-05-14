#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "headers/directionalLight.h"
#include "headers/light.h"
#include "../lib/headers/point.h"

DirectionalLight::DirectionalLight(): Light() {}

void DirectionalLight::draw(){
    Point p {this->POS()};
    float pos[4] {
        p.X(), p.Y(), p.Z(), 0.0f
    };

    glLightfv(GL_LIGHT0 + this->INDEX(), GL_POSITION, pos);
    glLightfv(GL_LIGHT0 + this->INDEX(), GL_AMBIENT, this->AMB());
    glLightfv(GL_LIGHT0 + this->INDEX(), GL_DIFFUSE, this->COLOR());
}
