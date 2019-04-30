#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "headers/light.h"
#include "../lib/headers/point.h"

Light::Light(int type, Point p): type(type), p(p) {
    this->i = -1;   
}

Light::~Light(){}

void Light::addIndex(int i){
    this->i = i;
}

void Light::draw(){
    float pos[4] {
        this->p.X(), this->p.Y(), this->p.Z(), 0
    };
    switch (this->type)
    {
        case POINT:
            glLightfv(GL_LIGHT0 + this->i, GL_POSITION, pos);
            break;
        case DIRECTIONAL:
            float dir[3] {pos[0], pos[1], pos[2]};
            glLightfv(GL_LIGHT0 + this->i, GL_SPOT_DIRECTION, dir);
            break;
        //case SPOT:
        //    glLightfv(GL_LIGHT0 + this->i, , )
        //    break;
    }
}