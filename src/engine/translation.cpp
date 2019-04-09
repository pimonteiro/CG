#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <vector>
#include <cmath>
#include "headers/translation.h"


void multMatrixVector(float, float, float);
float length(float);
void normalize(float);
void buildRotMatrix(float, float, float, float);
void cross(float, float, float);

Translation::Translation(): Transformation(Point()) {}

void
Translation::addPoint(Point* p)
{
        this->pointV.push_back(p);
}


void
Translation::addTime(float t)
{
        this->time = t;
}

Translation::~Translation() {}

void
Translation::transform()
{
        if (!this->pointV.empty())
                glTranslatef(this->pointV.at(0)->X(), this->pointV.at(0)->Y(), this->pointV.at(0)->Z());
}


void
buildRotMatrix(float *x, float *y, float *z, float *m)
{
        m[0] = x[0];
        m[1] = x[1];
        m[2] = x[2];
        m[3] = 0;
        m[4] = y[0];
        m[5] = y[1];
        m[6] = y[2];
        m[7] = 0;
        m[8] = z[0];
        m[9] = z[1];
        m[10] = z[2];
        m[11] = 0;
        m[12] = 0;
        m[13] = 0;
        m[14] = 0;
        m[15] = 1;
}

void
cross(float *a, float *b, float *res)
{
        res[0] = a[1] * b[2] - a[2] * b[1];
        res[1] = a[2] * b[0] - a[0] * b[2];
        res[2] = a[0] * b[1] - a[1] * b[0];
}

void
normalize(float *a)
{
        float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
        a[0] = a[0] / l;
        a[1] = a[1] / l;
        a[2] = a[2] / l;
}

float
length(float *v)
{
        float res = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
        return res;
}

void
multMatrixVector(float *m, float *v, float *res)
{
        for (int j = 0; j < 4; ++j) {
                res[j] = 0;

                for (int k = 0; k < 4; ++k)
                        res[j] += v[k] * m[j * 4 + k];
        }
}
