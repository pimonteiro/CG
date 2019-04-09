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
        this->pointArray = new float[this->size];
}

Model::~Model()
{
        if (this->pointArray != nullptr)
                delete [] this->pointArray;
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
Model::draw()
{
        float* verts {new float[this->size]};

        for (int index = 0;  index < this->size; index++)
                verts[index] = this->pointArray[index];

        glGenBuffers(1, this->buffer);
        glBindBuffer(GL_ARRAY_BUFFER, this->buffer[0]);
        glBufferData(GL_ARRAY_BUFFER, this->size * sizeof(float), verts, GL_STATIC_DRAW);
        delete [] verts;
        glBindBuffer(GL_ARRAY_BUFFER, this->buffer[0]);
        glVertexPointer(3, GL_FLOAT, 0, 0);
        glColor3f(this->r, this->g, this->b);
        glDrawArrays(GL_TRIANGLES, 0, (this->size) / 3);
        glDeleteBuffers(1, this->buffer);
}

