#include "headers/model.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif


Model::Model(int numberPoints)
{
        this->size = numberPoints * 3; /* each point has 3 floats */
        this->index = 0;
        this->buffer = new GLuint[1];
        this->pointArray = new float[this->size];
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
        glColor3f(this->r, this->g, this->b);
        glGenBuffers(1, this->buffer);
        glBindBuffer(GL_ARRAY_BUFFER, *this->buffer);
        glBufferData(GL_ARRAY_BUFFER, this->size * sizeof(float), this->pointArray, GL_STATIC_DRAW);
}

void
Model::draw()
{
        glBindBuffer(GL_ARRAY_BUFFER, *this->buffer);
        glVertexPointer(3, GL_FLOAT, 0, 0);
        glDrawArrays(GL_TRIANGLES, 0, (this->size) / 3);
}

