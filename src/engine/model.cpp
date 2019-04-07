#include "headers/model.h"
#include <iostream>
#include <random>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif


Model::Model()
{
}

Model::~Model()
{
        for (auto& t : this->triV)
                delete t;
}

void
Model::addElement(Triangle *triangle)
{
        triV.push_back(triangle);
}

void
Model::addColour(float r, float g, float b)
{
        this->r = r;
        this->g = g;
        this->b = b;
}

void
Model::draw()
{
        glColor3f(this->r, this->g, this->b);

        for (auto& t : this->triV)
                t->draw();
}

