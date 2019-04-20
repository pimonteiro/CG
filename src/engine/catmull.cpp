#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "headers/catmull.h"
#include "../lib/headers/matrix.h"
#include <cmath>

#define T_INCREMENT	0.0001

Catmull::Catmull(): Transformation(Point()) {
        float t[3] {0, 1, 0};
        setYAxis(t);
}

void Catmull::addFlag(int rot) {
        this->ownRotation = rot;
}

void Catmull::addTime(float t) {
        this->time = abs(t);
}

Catmull::~Catmull() {}

void Catmull::addPoint(Point *p) {
        this->contP.push_back(p);
}

int Catmull::getRotation() {
        return this->ownRotation;
}


void Catmull::setYAxis(float y[3]) {
        this->yAxis[0] = y[0];
        this->yAxis[1] = y[1];
        this->yAxis[2] = y[2];
}

Point Catmull::getCatmullRomPoint(float t, Point p0, Point p1, Point p2, Point p3, float *deriv) {
        float pp0[3] {p0.X(), p0.Y(), p0.Z()};
        float pp1[3] {p1.X(), p1.Y(), p1.Z()};
        float pp2[3] {p2.X(), p2.Y(), p2.Z()};
        float pp3[3] {p3.X(), p3.Y(), p3.Z()};
        float ppos[3];
        // catmull-rom matrix
        float m[4][4] {	{-0.5f,  1.5f, -1.5f,  0.5f},
                { 1.0f, -2.5f,  2.0f, -0.5f},
                {-0.5f,  0.0f,  0.5f,  0.0f},
                { 0.0f,  1.0f,  0.0f,  0.0f}
        };
        // Compute A = M * P
        float A[3][4];

        for (int i {0}; i < 3; i++) {
                float v[4] {pp0[i], pp1[i], pp2[i], pp3[i]};
                multMatrixVector(m[0], v, A[i]);
        }

        // Compute pos = T * A
        float T[4] {t *t * t, t * t, t, 1};

        for (int i { 0 }; i < 3; i++) {
                float v[4] {A[i][0], A[i][1], A[i][2], A[i][3]};
                ppos[i] = T[0] * v[0] + T[1] * v[1] + T[2] * v[2] + T[3] * v[3];
        }

        // compute deriv = T' * A
        float TT[4] {3 * t * t, 2 * t, 1, 0};

        for (int i {0}; i < 3; i++) {
                float v[4] {A[i][0], A[i][1], A[i][2], A[i][3]};
                deriv[i] = TT[0] * v[0] + TT[1] * v[1] + TT[2] * v[2] + TT[3] * v[3];
        }

        return Point(ppos[0], ppos[1], ppos[2]);
}

// given  global t, returns the point in the curve
Point Catmull::getGlobalCatmullRomPoint(float gt, float *deriv) {
        int nP { static_cast<int>(this->contP.size())};
        float t { gt * nP} ; // this is the real global t
        int index { static_cast<int>(floor(t)) };  // which segment
        t = t - index; // where within  the segment
        // indices store the points
        int indices[4];
        indices[0] = (index + nP - 1) % nP;
        indices[1] = (indices[0] + 1) % nP;
        indices[2] = (indices[1] + 1) % nP;
        indices[3] = (indices[2] + 1) % nP;
        return getCatmullRomPoint(t, *this->contP[indices[0]], *this->contP[indices[1]], *this->contP[indices[2]], *this->contP[indices[3]], deriv);
}

void Catmull::renderCatmullRomCurve() {
        glColor3f(1, 1, 1);
        glBegin(GL_LINE_LOOP);

        for (int i {0}; i < 10000; i++) {
                float t { 0.0001f * i} ;
                float deriv[3];
                Point pos {this->getGlobalCatmullRomPoint(t, deriv)};
                glVertex3f(pos.X(), pos.Y(), pos.Z());
        }

        glEnd();
}

void Catmull::transform() {
        renderCatmullRomCurve();
        float deriv[3];
        float tt { glutGet(GLUT_ELAPSED_TIME) / this->time };
        Point pos { this->getGlobalCatmullRomPoint(tt, deriv)};
        glTranslatef(pos.X(), pos.Y(), pos.Z());

        if (this->ownRotation) { // Rotates using self derivated rotation
                float zr[3];
                cross(deriv, this->yAxis, zr);
                float ty[3];
                cross(zr, deriv, ty);
                normalize(zr);
                normalize(deriv);
                normalize(ty);
                this->setYAxis(ty);
                float m[16];
                buildRotMatrix(deriv, ty, zr, m);
                glMultMatrixf(m);
        }
}