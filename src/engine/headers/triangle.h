#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "point.h"

class Triangle {
    private:
        Point *x, *y, *z;
        float r, g, b;
    public:
        Triangle();
        void addX(Point*);
        void addY(Point*);
        void addZ(Point*);
        Point* getX();
        Point* getY();
        Point* getZ();
        void draw();
};

#endif
