#include "headers/model.h"
#include <iostream>
#include <random>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

float
randomF()
{
        std::random_device seeder;
        std::mt19937 engine(seeder());
        std::uniform_real_distribution<float> dist(0, 1);
        return dist(engine);
}

Model::Model(int numberPoints)
{
        this->size = numberPoints;
        this->index = 0;
        this->buffer = new GLuint[1];
        this->pointArray = new float[this->size];
        this->r = randomF();
        this->g = randomF();
        this->b = randomF();
}

Model::~Model()
{
}

void
Model::addElement(float cord)
{
        this->pointArray[this->index++] = cord;
}

void
Model::addColour(float r, float g, float b)
{
        this->r = r;
        this->g = g;
        this->b = b;
}

void
Model::prepare()
{
        glGenBuffers(1, (this)->buffer);
        glBindBuffer(GL_ARRAY_BUFFER, *(this)->buffer);
        glBufferData(GL_ARRAY_BUFFER, this->size * sizeof(float), this->pointArray, GL_STATIC_DRAW);
}

void
Model::draw()
{
        glBindBuffer(GL_ARRAY_BUFFER, (this)->buffer[0]);
        glVertexPointer(3, GL_FLOAT, 0, 0);
        glColor3f(this->r, this->g, this->b);
        glDrawArrays(GL_TRIANGLES, 0, (this->size) - 1);
}

