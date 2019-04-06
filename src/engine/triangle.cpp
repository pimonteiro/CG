#include "headers/triangle.h"
#include "headers/point.h"
#include <iostream>
#include <random>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
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

Triangle::~Triangle()
{
        if (this->x != nullptr)
                delete this->x;

        if (this->y != nullptr)
                delete this->y;

        if (this->z != nullptr)
                delete this->z;
}

Triangle::Triangle()
{
        this->r = randomF();
        this->g = randomF();
        this->b = randomF();
}

void
Triangle::addX(Point* x)
{
        this->x = x;
}


void
Triangle::addY(Point* y)
{
        this->y = y;
}

void
Triangle::addZ(Point* z)
{
        this->z = z;
}


void
Triangle::drawC()
{
        glColor3f(this->r, this->g, this->b);
        glBegin(GL_TRIANGLES);
        glVertex3f(this->x->X(), this->x->Y(), this->x->Z());
        glVertex3f(this->y->X(), this->y->Y(), this->y->Z());
        glVertex3f(this->z->X(), this->z->Y(), this->z->Z());
        glEnd();
}


void
Triangle::draw()
{
        glBegin(GL_TRIANGLES);
        glVertex3f(this->x->X(), this->x->Y(), this->x->Z());
        glVertex3f(this->y->X(), this->y->Y(), this->y->Z());
        glVertex3f(this->z->X(), this->z->Y(), this->z->Z());
        glEnd();
}
