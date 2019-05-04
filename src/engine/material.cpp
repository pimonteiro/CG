#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "headers/material.h"

Material::Material(){
    this->type = NOSURFACE;
    this->r = 1;
    this->g = 1;
    this->b = 1;
}

Material::~Material(){}


void Material::addType(int t){
    this->type = t;
}

void Material::addColor(float r, float g, float b){
    this->r = r;
    this->g = g;
    this->b = b;
}

void Material::setup(){
    float color[4] {this->r, this->g, this->b, 1.0f};
    switch (this->type)
    {
        case DIFFUSE:
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
            break;
        case SPECULAR:
            glMaterialfv(GL_FRONT, GL_SPECULAR, color);
            break;
        case EMISSIVE:
            glMaterialfv(GL_FRONT, GL_EMISSION, color);
            break;
        case AMBIENTE:
            glMaterialfv(GL_FRONT, GL_AMBIENT, color);
            break;
        default:
            glColor3fv(color);
            break;
    }
}
