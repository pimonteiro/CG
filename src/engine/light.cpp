#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "headers/light.h"
#include "../lib/headers/point.h"


Light::Light(Point p): pos(p) {
    this->i = -1;
    float defColor[4] {1,1,1,1};
    float defAmb[4] {0,0,0,1};
    for(int i = 0; i < 4; i++){
        this->color[i] = defColor[i];
        this->amb[i] = defAmb[i];
    }
}

Light::~Light(){}

void Light::setColor(float c[4]){
    for(int i = 0; i < 4; i++)
        this->color[i] = c[i];
}

void Light::setAmb(float c[4]){
    for(int i = 0; i < 4; i++){
        this->amb[i] = c[i];
    }
}

void Light::setIndex(int i){
    this->i = i;
}

void Light::turnOn(){
    glEnable(GL_LIGHT0 + this->i);
}

void Light::turnOff(){
    glDisable(GL_LIGHT0 + this->i);
}
